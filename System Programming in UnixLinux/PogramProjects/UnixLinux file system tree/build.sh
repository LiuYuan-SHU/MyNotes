if [ -f test ]
then
    echo "删除test...."
    rm test
fi

if [ -f system ]
then
    echo "删除system...."
    rm system
fi

echo "编译程序...."
echo

make -f makefile

echo "编译结束"
echo