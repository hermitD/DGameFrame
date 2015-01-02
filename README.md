#CC-DGame
everything begin with the win API

1: make the Api to a App Framework
2: make the app frame to a Game frame
//3: the pure game thing , maybe use Easy X or other lib about the 2D?
(haven't done :( )
//4: maybe with 3 network? with past codes?
(haven't done :( )

1
in main ,There's nothing other but the main frame codes. It's auto run by the main.
we use virtual func to let it run various app?

MFC
CXXApp 继承 CWinApp 包含 CMainFrame
CMainFrame 继承CWnd 包含 CDocu & CView



怎么使得一个固定的框架去执行不同的app呢？那么就是其执行的是基类的指针那么可以指向子类的实例。通过虚函数多态实现子类的相应函数重载来实现多样性，但是如何保证框架里的基类指针能够自动的去指向相应的子类呢？那么就要利用一些程序内部的特性来实现，比如全局变量是先于所有代码执行的。

Windows API没有设计为支持面向对象的语言，WndProc属于全局函数。

窗口回调函数里面需要一个得到指定窗口对象的指针。
将窗口对象指针保存在窗口类所制定的额外数据结构中。然后在回调函数中获取相应函数，然后调用其消息函数。

DWnd to abstract a usual wnd
DMainFrame to abstract a DWnd






