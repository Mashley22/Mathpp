#!/usr/bin/env python3
import re
import sys


COLUMNS = ['Implementation', 'Mean', 'Std Dev', 'Min', 'Max', 'Range']

def parse_benchmark_data(text):
    """Parse the benchmark data into a list of dictionaries."""
    blocks = re.split(r'={3,}\n', text.strip())
    results = []
    
    for block in blocks:
        if not block.strip():
            continue
        
        data = {}
        lines = block.strip().split('\n')
        
        # Parse header (e.g., "abs:std_abs32")
        header = lines[0].strip()
        if ':' in header:
            category, implementation = header.split(':')
            data['Category'] = category
            data['Implementation'] = implementation
        else:
            data['Implementation'] = header
        
        # Parse statistics
        for line in lines[1:]:
            line = line.strip()
            if ':' in line:
                key, value = line.split(':', 1)
                key = key.strip()
                value = value.strip()
                
                # Convert to appropriate type
                try:
                    if '.' in value:
                        data[key] = float(value)
                    else:
                        data[key] = int(value)
                except ValueError:
                    data[key] = value
        
        results.append(data)
    
    return results

def create_markdown_table(results, columns=None, decimal_places=2):
    """Convert parsed results into a markdown table."""
    if not results:
        return "No data to display."
    
    # Determine columns to display
    if columns is None:
        columns = COLUMNS

    # Create header
    header = "| " + " | ".join(columns) + " |"
    separator = "|" + "|".join(["---" for _ in columns]) + "|"
    
    # Create rows
    rows = []
    for result in results:
        row_values = []
        for col in columns:
            value = result.get(col, '')
            
            # Format numbers
            if isinstance(value, float):
                value = f"{value:.{decimal_places}f}"
            elif isinstance(value, int) and col in ['Min', 'Max', 'Median']:
                value = f"{value:,}"
            
            row_values.append(str(value))
        rows.append("| " + " | ".join(row_values) + " |")
    
    return header + "\n" + separator + "\n" + "\n".join(rows)

def create_summary_markdown_table(results, decimal_places=2):
    """Create a more detailed markdown table with all statistics."""
    if not results:
        return "No data to display."
    
    columns = ['Implementation', 'Category', 'Mean', 'Std Dev', 'Variance', 
               'Min', 'Max', 'Range', 'Median']
    
    header = "| " + " | ".join(columns) + " |"
    separator = "|" + "|".join(["---" for _ in columns]) + "|"
    
    rows = []
    for result in results:
        row_values = []
        for col in columns:
            value = result.get(col, '')
            
            if isinstance(value, float):
                if col == 'Variance':
                    value = f"{value:,.2f}"
                else:
                    value = f"{value:,.{decimal_places}f}"
            elif isinstance(value, int):
                value = f"{value:,}"
            
            row_values.append(str(value))
        rows.append("| " + " | ".join(row_values) + " |")
    
    return header + "\n" + separator + "\n" + "\n".join(rows)

def main():
    """Main function to process input and generate markdown tables."""
    if len(sys.argv) > 1:
        # Read from file
        with open(sys.argv[1], 'r') as f:
            text = f.read()
    else:
        # Read from stdin
        text = sys.stdin.read()
    
    results = parse_benchmark_data(text)
    
    # Print different table formats
    print("## Performance Comparison\n")
    print(create_markdown_table(results, 
                               columns=COLUMNS))
    
    print("\n## Detailed Statistics\n")
    print(create_summary_markdown_table(results))
    
    # Group by category
    categories = {}
    for result in results:
        cat = result.get('Category', 'Uncategorized')
        if cat not in categories:
            categories[cat] = []
        categories[cat].append(result)
    
    print("\n## Comparison by Category\n")
    for category, cat_results in categories.items():
        print(f"### {category}\n")
        print(create_markdown_table(cat_results,
                                   columns=COLUMNS))
        print()

if __name__ == "__main__":
    main()
