# 扩展版本生命游戏
这是一个用C++实现的生命游戏。

## 主要工作
* 用C++复现了Conway的生命游戏，借助ege库实现可视化
* 实现了生命游戏的一种拓展
* 引入个体移动策略，模拟生命的迁徙行为
* 支持对移动策略中的超参数进行设置
* 支持探索不同超参数情况下的个体存活数，以便寻找最佳的超参数组合
* 支持运行多次计算个体平均存活数
* 每次运行可以在进化稳定时提前结束（即：无需迭代到最大次数）
* 采用命令行模式整合多种功能，支持运行时参数调整

## 编译与配置说明
* 本游戏借助了ege库，为了编译代码，须事先安装配置该库（目前版本使用了EGE 24.04）
* 提供的代码经Dev-C++ 5.11环境编译测试

## 命令行说明
* 本程序的命令行有三种格式：
（1）gameoflife ori <max_iter_everytime> <times>
（2）gameoflife try <max_iter_everytime> <max_d>
（3）gameoflife set <max_iter_everytime> <d> <rational_count> <times>

## 联系方式
* 有任何问题，请联系zrchen@mail.ustc.edu.cn
