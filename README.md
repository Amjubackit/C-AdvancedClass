# C-AdvancedClass

## Run test data with the following command:
```gcc ex1_q1.c -o ex1_q1 && grep -v '^#' test_data_q1.txt | while read -r line; do echo "$line" |./ex1_q1 |grep -e '{' -e 'k:'; echo '=================='; done```

## Recompile & Run task 2 using test data:
```gcc ex1_q2.c -o ex1_q2 && grep -v '^#' test_data_q2.txt | while read -r line; do echo "$line" |./ex1_q2; echo '=================='; done```
