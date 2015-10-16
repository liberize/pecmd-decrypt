# pecmd-decrypt

解密 mdyblog 版 pecmd 加密的 pecmd.ini。

## 原理

其实准确说“解密”无关，目前之所以没有破解只是因为算法没公开，我也没有去研究它的算法，
反正不管怎样，最后肯定要解出来才能执行，所以我在执行的地方替换了它调用的系统 API，从 API 参数里面拿到了解出来的脚本。

pecmd 执行每一行的时候会将其转为 unicode 编码，会调用 `MultiByteToWideChar` 这个 API，只要 hook 这个  API，从 `lpMultiByteStr` 参数得到传入的多字节字符串，过滤一下就可以得到原始内容。

用 [detours](http://research.microsoft.com/en-us/projects/detours/) 可以很方便地达到这个目的：

1. 编写一个 dll，实现一个新的 `MultiByteToWideChar` 函数，在 DllMain 里面使用 detours 替换原来的函数；
2. 编写一个加载器，使用 detours 启动 pecmd 进程，并注入我们的 dll。

## 说明

理论上此方法适用于使用所有加密方式加密的 ini，不限于 CMPS/CMPA。

用什么版本的 pecmd.exe 其实无所谓，但是最近的 m 版 pecmd，启动时会执行一个内置脚本，这个脚本的内容也会出现在生成的 ini 文件中，为了避免混在一起无法区分，请使用不会执行内置脚本的 pecmd。
判断方法：用一个没有加密的脚本去跑，如果解出来是一样的，那么就不会执行内置脚本。

## 步骤

本人比较懒，所以直接发布简陋的命令行工具，没有做成 GUI 工具。**以下步骤在 PE 下进行**。

1. 先得到加密的 pecmd.ini，如果内置于 pecmd.exe，请用 res hacker 提取；
2. 找一个不会执行内置脚本的 pecmd.exe，32/64 位其实无所谓，只要 PE 能运行就可以；
3. 下载 [pecmd-decrypt](https://github.com/liberize/pecmd-decrypt/releases)，使用与 pecmd.exe 对应的版本，比如 pecmd.exe 是 64 位的就使用 x64 文件夹中的版本；
4. 将 1、2 里面的 pecmd.exe 和 pecmd.ini 放在 x86/x64 这个目录下；
5. 打开终端，运行 `DetourHook.exe "pecmd.exe pecmd.ini" DetourHookDll.dll`；
6. 在当前目录生成 original.ini，便是解密后的 pecmd.ini。
