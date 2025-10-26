for infile in ./meteorobservation_data/secret/*.in; do
    # Get the base name without the .in extension
    base="${infile%.in}"
    # echo "base is ${base}"
    # Run the executable and redirect input/output
    ./a.out < "$infile" > "${base}.out"
    echo "diff for ${base} is:"
    diff -yw "${base}.out" "${base}.ans"
done