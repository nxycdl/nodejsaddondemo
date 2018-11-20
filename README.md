首先使用node addon 我只在windows上面测试了;
1. nodejs 的版本很重要，我调用的DLL是32位的，如果node 的版本是64位的，那么在调用的时候回出现windows 错误 193 ;
2. 在nxmi 文件目录的内容是关于node调用nxmi.dll的源码;
3. 在nxmi里面初始化一个package
4. 新建binding.gyp
5. 新建nxmi.cc 存放c++调用DLL的源码（网上有，需要注意c++调用DLL类型的处理)
6. 使用node-gyp configure rebuild 编译生成nxmi.node ；
7. 生成nxmi.node 后可以现在nodejs的环境下面测试是否正常运行;
7. 新建main.js 导出你写的函数;
8. 拷贝你生成的这些文件到 其他工程的 node_module 目录下;
9. 如果在electron环境调用nxmi.node ;需要重新使用 electron 编译
10.编译命令（测试-arch命令待定）：  HOME=~/.electron-gyp node-gyp rebuild --target=3.0.10 --dist-url=https://atom.io/download/electron
11.如果出现nan冲突，那么需要 删除nxmi目录里面package 对nan的依赖， 然后在你的工程目录安装nan;
12.在你的electron 的package 里面增加nxmi  dependencies 否则运行的时候提示找不到nxmi;
13.在你打包好的文件中放上你的dll文件，运行程序进行测试；