#!/bin/bash
#lab33.sh
# 检测数字中是否有3
has_three_digit() {
    local number=$1
    # 用模式匹配检查是否包含3
    if [[ "$number" == *"3"* ]]; then
        return 0  # 有3
    else
        return 1  # 没有3
    fi
}
# select
select_numbers() {
    local limit=$1
    local total=0
    
    echo "在1到$limit 范围内筛选结果："
    echo "========================"
    
    for ((num=1; num<=limit; num++)); do
        # 跳过3的倍数
        if [ $((num % 3)) -eq 0 ]; then
            continue
        fi
        
        # 跳过包含3的数字
        if has_three_digit "$num"; then
            continue
        fi
        
        # 输出符合条件的
        printf "%d " "$num"
        total=$((total + 1))
        
        # 每行输出10个数字
        if [ $((total % 10)) -eq 0 ]; then
            printf "\n"
        fi
    done
    
    # 换行
    if [ $((total % 10)) -ne 0 ]; then
        printf "\n"
    fi
    echo "========================"
    echo "符合要求的数字总数: $total"
}

# main
run_main() {
    # 参数检查
    if [ $# -ne 1 ]; then
        echo "使用方式: $0 <正整数n>"
        echo "例子: $0 50"
        exit 1
    fi
    
    local input_num=$1
    
    # 输入是否为正整数
    if ! [[ "$input_num" =~ ^[1-9][0-9]*$ ]]; then
        echo "输入错误：请提供正整数"
        exit 1
    fi
    
    # 大数字提示
    if [ "$input_num" -gt 10000 ]; then
        echo "提示：数值较大，处理中请稍候..."
    fi
    
    # 执行筛选
    select_numbers "$input_num"
}

# 交互模式
run_interactive() {
    while true; do
        echo
        echo "请输入正整数n（输入exit退出）："
        read -r user_input
        
        if [ "$user_input" = "exit" ] || [ "$user_input" = "EXIT" ]; then
            echo "程序退出"
            break
        fi
        
        if ! [[ "$user_input" =~ ^[1-9][0-9]*$ ]]; then
            echo "输入无效：请输入正确的正整数"
            continue
        fi
        
        if [ "$user_input" -gt 100000 ]; then
            echo "数值过大，请重新输入（推荐小于100000）"
            continue
        fi
        
        select_numbers "$user_input"
    done
}
# 程序入口
if [ $# -eq 1 ]; then
    run_main "$1"
else
    echo "数值筛选工具"
    echo "功能：输出1-n之间的整数，排除含3的数字和3的倍数"
    run_interactive
fi
