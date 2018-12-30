from PIL import Image, ImageFont, ImageDraw

def white_to_transparent(img):
    """
    """

    img = img.convert('RGBA') #返回一个转换后的图像副本
    datas = img.getdata()
    newData = []
    for item in datas:
        if item[0] == 255 and item[1] == 255:
            newData.append((255,255,255,0))
        else:
            newData.append(item)
    img.putdata(newData) #赋值给图片新的像素数据
    return img

if __name__ == "__main__":
    p1_name = "github_logo"
    p2_name = "red_reminder"
    p1_image = Image.open(p1_name)
    p2_image = Image.open(p2_name)
    p2_transparent=white_to_transparent(p2_image)
    p1_image.paste(p2_transparent,(0,0),p2_transparent)#paste方法?

    usr_font=ImageFont.truetype("usr/share/fonts/truetype\
                                 /deepin/DeepinOpenSymbol.ttf",32)
            #If"can't open resource" it means, can't find font.
            #Use absolut path, rather than relative path.
    draw=ImageDraw.Draw(p1_image) #在p1_image上绘制文字，图像
    draw.text((152,8),u'0',font=usr_font)
    p1_image.save("final.png","PNG")
