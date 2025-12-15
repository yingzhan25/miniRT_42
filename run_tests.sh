#!/bin/bash

echo "=== MiniRT Parser Tests ==="
echo ""

if [ ! -d "src/scenes/valid" ]; then
    echo "ERROR: scenes/valid/ directory not found"
    exit 1
fi

if [ ! -d "src/scenes/errors" ]; then
    echo "ERROR: scenes/errors/ directory not found"
    exit 1
fi

echo "Testing VALID files (should pass):"
echo "---------------------------------"

for file in src/scenes/valid/*.rt; do
    if [ -f "$file" ]; then
        filename=$(basename "$file")
        ./minirt "$file" > /dev/null 2>&1

        if [ $? -eq 0 ]; then
            echo "✓ $filename"
        else
            echo "✗ $filename - FAILED"
            echo "  Running with error output:"
            ./minirt "$file" 2>&1 | sed 's/^/    /'
        fi
    fi
done

echo ""
echo "Testing ERROR files (should fail):"
echo "----------------------------------"

for file in src/scenes/errors/*.rt; do
    if [ -f "$file" ]; then
        filename=$(basename "$file")
        ./minirt "$file" > /dev/null 2>&1

        if [ $? -ne 0 ]; then
            echo "✓ $filename (correctly failed)"
        else
            echo "✗ $filename - SHOULD HAVE FAILED BUT PASSED"
        fi
    fi
done

echo ""
echo "=== Tests Complete ==="