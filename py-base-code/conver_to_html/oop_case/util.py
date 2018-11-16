'''
文本块生成器
'''
def lines(file):
    '''
    生成器lines在文件末尾添加空行
    '''
    for line in file:
        yield line
    yield '\n'

def blocks(file):
    '''
    生成文本快时将一个段落的所有行合并
    '''
    block = []
    for line in lines(file):
        if line.strip():
            block.append(line)
        elif block:
            yield ''.join(block).strip()
            block = []
