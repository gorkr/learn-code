from PIL import Image, ImageFont, ImageDraw

def white_to_transparent(img):
    """抠图"""

    #convert()函数，用于不同模式图像之间的转换。
    #PIL中有九种不同模式，分别为1，L，P，RGB，RGBA，CMYK，YCbCr，I，F。
    #模式“1”为二值图像，非黑即白。模式“L”为灰色图像.模式“P”为8位彩色图像.模式“RGBA”为32位彩色图像.
    #模式“I”为32位整型灰色图像.模式“F”为32位浮点灰色图像.
    img = img.convert('RGBA') #返回一个转换后的图像副本
    datas = img.getdata()  #像素数据队列
    newData = []
    for item in datas:
        if item[0] == 255 and item[1] == 255:
            newData.append((255,255,255,0))  #把白色变为透明色
        else:
            newData.append(item)
    img.putdata(newData) #赋值给图片新的像素数据
    img.save("change.png","PNG")
    return img

if __name__ == "__main__":
    p1_name = "github_logo"  #the path of image.
    p2_name = "red_reminder"
    p1_image = Image.open(p1_name)  #make a Image object
    p2_image = Image.open(p2_name)
    p2_transparent=white_to_transparent(p2_image)
    p1_image.paste(p2_transparent,(0,0),p2_transparent)  #paste方法?

    #usr_font=ImageFont.truetype("usr/share/fonts/truetype\
    #                             /deepin/DeepinOpenSymbol.ttf",32)
    usr_font = ImageFont.truetype("./FZZCHJW.TTF",32)
            #If"can't open resource" it means, can't find font.
            #Use absolut path, rather than relative path.
    draw=ImageDraw.Draw(p1_image) #在p1_image上绘制文字，图像
    draw.text((152,8),u'10',font=usr_font)
    p1_image.save("final.png","PNG")
