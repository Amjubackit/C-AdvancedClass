# C-AdvancedClass
## Run test data with the following command:
```grep -v '^#' test_data.txt | while read -r line; do echo "$line" |./source1 |grep -e '{' -e 'k:'; echo '=================='; done```