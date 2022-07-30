# C-AdvancedClass
## Run test data with the following command:
```grep -v '^#' test_data_q1.txt | while read -r line; do echo "$line" |./ex1_q2 |grep -e '{' -e 'k:'; echo '=================='; done```