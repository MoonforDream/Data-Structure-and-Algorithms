import re

def convert_image_links(md_file,new_url):
    with open(md_file, 'r', encoding='utf-8') as file:
        content = file.read()
    new_prefix = new_url.replace('\\', '/') + '/'
    old_prefix = 'https://github.com/MoonforDream/Data-Structure-and-Algorithms/blob/main/images/'
    pattern = r'<img src="' + re.escape(old_prefix) + r'([^"]+)">'
    repl = '<img src="' + new_prefix + r'\1">'

    # 替换图片链接为 <img src="new_url/">
    converted_content = re.sub(pattern, repl, content)

    # 将转换后的内容写回原文件
    with open(md_file, 'w', encoding='utf-8') as file:
        file.write(converted_content)

# 调用函数将指定的Markdown文件中的图片链接进行转换
#new_url就是你下载图片的文件夹路径
convert_image_links(r"D:\Desktop\C++后台开发\数据结构与算法\graph(图).md",r"C:\Users\me\AppData\Roaming\Typora\typora-user-images")
