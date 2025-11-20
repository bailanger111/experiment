#!/bin/bash

DIR="/home/buyhorse1/records/01-bigc"
MY_ACCOUNT="bigc1553"

# 检查目录
if [ ! -d "$DIR" ]; then
    echo "错误: 不存在"
    exit 1
fi
# 临时文件
TEMP=$(mktemp)
echo "正在处理出勤记录..."

# 处理每个文件
for file in "$DIR"/*; do
    if [ -f "$file" ]; then
        # 文件名作为日期标识
        filename=$(basename "$file")
        
        # 提取所有bigc+4位数字
        grep -oE 'bigc[0-9]{4}' "$file" | sort -u | while read student; do
            echo "$filename:$student"
        done
    fi
done > "$TEMP"

# 统计出勤次数（按文件去重）
echo "学生出勤统计:"
# 使用awk进行统计和排序
awk -F: '
!seen[$1,$2]++ { 
    count[$2]++ 
} 
END {
    # find自己
    for (student in count) {
        if (student == "'"$MY_ACCOUNT"'") {
            my_count = count[student]
        } else {
            other[student] = count[student]
        }
    }
    # 按账号排序
    n = asorti(count, sorted)
    for (i = 1; i <= n; i++) {
        printf "%s: %d\n", sorted[i], count[sorted[i]]
    }
    
    # 自己
    print ""
    print "自己的出勤统计:"
    printf "%s: %d\n", "'"$MY_ACCOUNT"'", my_count
}' "$TEMP"

# 清理临时文件
rm -f "$TEMP"
