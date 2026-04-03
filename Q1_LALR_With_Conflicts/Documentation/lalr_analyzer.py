#!/usr/bin/env python3
"""
LALR(1) Automaton Analyzer
Parses bison output and generates detailed conflict analysis with visualization
"""

import re
import sys
from collections import defaultdict

def parse_bison_output(filename):
    """Parse the bison .output file"""
    with open(filename, 'r') as f:
        content = f.read()
    
    # Extract grammar rules
    grammar_section = re.search(r'Grammar\n\n(.*?)(?=\n\nTerminals|Nonterminals|State)', content, re.DOTALL)
    rules = {}
    if grammar_section:
        for line in grammar_section.group(1).split('\n'):
            match = re.match(r'\s*(\d+)\s+(.+?):\s+(.+)', line)
            if match:
                rule_num, lhs, rhs = match.groups()
                rules[int(rule_num)] = (lhs, rhs)
    
    # Extract states
    states = {}
    state_pattern = r'State (\d+)(.*?)(?=State \d+|\Z)'
    for match in re.finditer(state_pattern, content, re.DOTALL):
        state_num = int(match.group(1))
        state_content = match.group(2)
        states[state_num] = parse_state(state_content, state_num)
    
    return rules, states

def parse_state(content, state_num):
    """Parse individual state content"""
    state_info = {
        'num': state_num,
        'items': [],
        'conflicts': {'sr': [], 'rr': []},
        'transitions': {}
    }
    
    # Check for conflicts in first line
    conflict_match = re.search(r'conflicts:\s+(\d+)\s+shift/reduce|(\d+)\s+reduce/reduce', content)
    if conflict_match:
        if 'shift/reduce' in content.split('\n')[0]:
            state_info['conflicts']['sr'] = ['shift/reduce conflict']
        if 'reduce/reduce' in content.split('\n')[0]:
            num_conflicts = re.search(r'(\d+)\s+reduce/reduce', content.split('\n')[0])
            if num_conflicts:
                state_info['conflicts']['rr'] = [f"{num_conflicts.group(1)} reduce/reduce conflicts"]
    
    # Extract items (productions with dots)
    for line in content.split('\n'):
        # Match items like: "26 stmt_block: '{' stmt_list '}' •"
        item_match = re.match(r'\s*(\d+)\s+(.+?):\s+(.+?)•(.*)', line)
        if item_match:
            rule_num, lhs, before_dot, after_dot = item_match.groups()
            state_info['items'].append({
                'rule': int(rule_num),
                'lhs': lhs,
                'before': before_dot.strip(),
                'after': after_dot.strip()
            })
        
        # Extract transitions
        trans_match = re.match(r'\s+(\S+)\s+(shift, and go to state|go to state|reduce using rule)\s+(.+)', line)
        if trans_match:
            symbol, action_type, target = trans_match.groups()
            if 'shift' in action_type or 'go to' in action_type:
                match_num = re.search(r'(\d+)', target)
                if match_num:
                    state_info['transitions'][symbol] = ('shift' if 'shift' in action_type else 'goto', int(match_num.group(1)))
            elif 'reduce' in action_type:
                match_num = re.search(r'(\d+)', target)
                if match_num:
                    state_info['transitions'][symbol] = ('reduce', int(match_num.group(1)))
        
        # Check for conflict markers [reduce using rule ...]
        conflict_reduce = re.search(r'\[reduce using rule (\d+)', line)
        if conflict_reduce:
            symbol_match = re.match(r'\s+(\S+)', line)
            if symbol_match and not state_info['conflicts']['rr']:
                state_info['conflicts']['rr'].append(f"reduce/reduce on {symbol_match.group(1)}")
    
    return state_info

def generate_dot_file(rules, states, output_file):
    """Generate Graphviz DOT file for automaton visualization"""
    
    with open(output_file, 'w') as f:
        f.write('digraph LALR_Automaton {\n')
        f.write('  rankdir=LR;\n')
        f.write('  node [shape=rectangle, fontname="Courier New", fontsize=10];\n')
        f.write('  edge [fontname="Courier New", fontsize=9];\n\n')
        
        # Create nodes for each state
        for state_num, state in sorted(states.items()):
            # Limit items shown to avoid clutter
            items_str = ""
            for i, item in enumerate(state['items'][:3]):  # Show max 3 items
                before = item['before'] if item['before'] else 'ε'
                after = item['after'] if item['after'] else ''
                items_str += f"{item['lhs']} → {before} • {after}\\l"
            
            if len(state['items']) > 3:
                items_str += f"... ({len(state['items'])-3} more)\\l"
            
            # Mark conflict states
            color = 'black'
            style = 'solid'
            if state['conflicts']['sr'] or state['conflicts']['rr']:
                color = 'red'
                style = 'bold'
                items_str += "\\l*** CONFLICT ***\\l"
                if state['conflicts']['rr']:
                    items_str += f"{state['conflicts']['rr'][0]}\\l"
            
            label = f"State {state_num}\\l{items_str}"
            f.write(f'  s{state_num} [label="{label}", color="{color}", style="{style}"];\n')
        
        f.write('\n')
        
        # Create edges for transitions
        transition_groups = defaultdict(list)
        for state_num, state in states.items():
            for symbol, (action, target) in state['transitions'].items():
                if action in ['shift', 'goto']:
                    transition_groups[(state_num, target)].append(symbol)
        
        for (src, dst), symbols in transition_groups.items():
            label = ', '.join(symbols[:3])  # Show max 3 symbols
            if len(symbols) > 3:
                label += f', +{len(symbols)-3}'
            f.write(f'  s{src} -> s{dst} [label="{label}"];\n')
        
        f.write('}\n')

def generate_state_table(states, output_file):
    """Generate state transition table"""
    
    # Collect all symbols
    all_symbols = set()
    for state in states.values():
        all_symbols.update(state['transitions'].keys())
    
    terminals = sorted([s for s in all_symbols if s.isupper() or s in ['(', ')', '{', '}', ';', ',', '?', '$end']])
    nonterminals = sorted([s for s in all_symbols if s not in terminals])
    
    with open(output_file, 'w') as f:
        f.write("=" * 150 + "\n")
        f.write("LALR(1) STATE TRANSITION TABLE\n")
        f.write("=" * 150 + "\n\n")
        
        # Header
        header = f"{'State':<8} | "
        header += " ".join([f"{s:<12}" for s in terminals[:10]])  # Limit terminals shown
        header += " | "
        header += " ".join([f"{s:<15}" for s in nonterminals[:8]])  # Limit nonterminals shown
        f.write(header + "\n")
        f.write("-" * 150 + "\n")
        
        # Rows
        for state_num in sorted(states.keys())[:50]:  # Limit to first 50 states
            state = states[state_num]
            row = f"{state_num:<8} | "
            
            for term in terminals[:10]:
                if term in state['transitions']:
                    action, target = state['transitions'][term]
                    if action == 'shift':
                        row += f"s{target:<11} "
                    elif action == 'reduce':
                        row += f"r{target:<11} "
                    else:
                        row += f"g{target:<11} "
                else:
                    row += " " * 12
            
            row += " | "
            
            for nonterm in nonterminals[:8]:
                if nonterm in state['transitions']:
                    action, target = state['transitions'][nonterm]
                    row += f"{target:<15} "
                else:
                    row += " " * 15
            
            f.write(row + "\n")
        
        if len(states) > 50:
            f.write(f"\n... ({len(states)-50} more states) ...\n")

def generate_conflict_report(rules, states, output_file):
    """Generate detailed conflict analysis report"""
    
    with open(output_file, 'w') as f:
        f.write("=" * 100 + "\n")
        f.write("LALR(1) CONFLICT ANALYSIS REPORT\n")
        f.write("=" * 100 + "\n\n")
        
        conflict_states = [s for s in states.values() if s['conflicts']['sr'] or s['conflicts']['rr']]
        
        f.write(f"Total States: {len(states)}\n")
        f.write(f"States with Conflicts: {len(conflict_states)}\n\n")
        
        if not conflict_states:
            f.write("No conflicts found!\n")
            return
        
        for state in conflict_states:
            f.write("=" * 100 + "\n")
            f.write(f"STATE {state['num']}: CONFLICT DETECTED\n")
            f.write("=" * 100 + "\n\n")
            
            # Show conflict type
            if state['conflicts']['rr']:
                f.write("CONFLICT TYPE: REDUCE/REDUCE\n\n")
                f.write("DESCRIPTION:\n")
                f.write("  The parser cannot decide which production to reduce when it sees certain lookahead symbols.\n")
                f.write("  Multiple reductions are possible, creating ambiguity.\n\n")
            
            if state['conflicts']['sr']:
                f.write("CONFLICT TYPE: SHIFT/REDUCE\n\n")
                f.write("DESCRIPTION:\n")
                f.write("  The parser cannot decide whether to shift the next token or reduce by a production.\n\n")
            
            # Show items in this state
            f.write("ITEMS IN THIS STATE:\n")
            for item in state['items']:
                before = item['before'] if item['before'] else 'ε'
                after = item['after'] if item['after'] else ''
                rule_info = rules.get(item['rule'], ('', ''))
                f.write(f"  [{item['rule']}] {item['lhs']} → {before} • {after}\n")
            
            f.write("\n")
            
            # Show conflicting productions
            if state['conflicts']['rr']:
                f.write("PRODUCTIONS INVOLVED IN REDUCE/REDUCE CONFLICT:\n")
                for item in state['items']:
                    if not item['after']:  # Complete items
                        rule_info = rules.get(item['rule'], ('', ''))
                        f.write(f"  Production {item['rule']}: {item['lhs']} → {item['before']}\n")
                f.write("\n")
            
            # Show transitions with conflicts
            f.write("TRANSITIONS (showing conflicts):\n")
            symbol_actions = defaultdict(list)
            for symbol, (action, target) in state['transitions'].items():
                symbol_actions[symbol].append((action, target))
            
            for symbol, actions in sorted(symbol_actions.items()):
                if len(actions) > 1 or any(a[0] == 'reduce' for a in actions):
                    f.write(f"  On '{symbol}':\n")
                    for action, target in actions:
                        if action == 'shift':
                            f.write(f"    - SHIFT and go to state {target}\n")
                        elif action == 'reduce':
                            rule_info = rules.get(target, ('', ''))
                            f.write(f"    - REDUCE by rule {target}: {rule_info[0]} → {rule_info[1]}\n")
            
            f.write("\n")
            
            # Explanation
            if state['conflicts']['rr']:
                f.write("EXPLANATION:\n")
                f.write("  When the parser reaches this state and sees the lookahead symbols, it has completed\n")
                f.write("  multiple productions and cannot determine which one to reduce. This is a reduce/reduce\n")
                f.write("  conflict. The grammar is ambiguous at this point.\n\n")
                
                f.write("RESOLUTION:\n")
                f.write("  Bison resolves this by choosing the production that appears first in the grammar.\n")
                f.write("  However, this may not match the intended semantics. Consider:\n")
                f.write("  1. Refactoring the grammar to eliminate the ambiguity\n")
                f.write("  2. Using different non-terminals for different contexts\n")
                f.write("  3. Adding precedence rules if appropriate\n\n")
            
            f.write("\n")

def main():
    if len(sys.argv) < 2:
        output_file = 'golem.output'
    else:
        output_file = sys.argv[1]
    
    print(f"Analyzing LALR(1) automaton from {output_file}...")
    
    # Parse bison output
    rules, states = parse_bison_output(output_file)
    
    print(f"Found {len(rules)} grammar rules")
    print(f"Found {len(states)} states")
    
    # Generate outputs
    print("\nGenerating conflict analysis report...")
    generate_conflict_report(rules, states, 'conflict_report.txt')
    
    print("Generating DOT file for automaton visualization...")
    generate_dot_file(rules, states, 'automaton.dot')
    
    print("Generating state transition table...")
    generate_state_table(states, 'state_table.txt')
    
    print("\n" + "=" * 80)
    print("ANALYSIS COMPLETE!")
    print("=" * 80)
    print("\nGenerated files:")
    print("  1. conflict_report.txt  - Detailed conflict analysis")
    print("  2. automaton.dot        - Graphviz DOT file (use: dot -Tpng automaton.dot -o automaton.png)")
    print("  3. state_table.txt      - State transition table")
    print("\nTo visualize the automaton:")
    print("  dot -Tpng automaton.dot -o automaton.png")
    print("  or")
    print("  dot -Tpdf automaton.dot -o automaton.pdf")

if __name__ == '__main__':
    main()
