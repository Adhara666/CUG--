import cv2
import os
import numpy as np
import matplotlib.pyplot as plt
# 设置matplotlib支持中文显示
plt.rcParams["font.family"] = ["SimHei"]  # 仅使用黑体
plt.rcParams['axes.unicode_minus'] = False  # 解决负号显示问题
from osgeo import gdal


"""opencv读取并处理图像
包含使用OpenCV读取图像,显示图像(彩色、单波段、灰度),计算协方差矩阵,绘制直方图,OTSU分割"""
class image_Processor_OpenCV:

    def __init__(self):
        #支持的图像格式列表
        self.supported_formats = ['.jpg', '.jpeg', '.png', '.bmp', '.tiff', '.tif']
        
        #窗口默认大小
        self.default_window_size = (800, 600)
        
        #波段名称映射
        self.band_names = ['Blue', 'Green', 'Red']

    """预处理中文窗口名称，以防出现乱码"""
    def _prepare_window_name(self, window_Name):
        try:
            return window_Name.encode('gbk')
        except UnicodeEncodeError:
            #转换失败则默认使用ImageProcessor作为标题
            window_Name = 'ImageProcessor'
            return window_Name

    """创建窗口并显示图像"""
    def _create_window(self, window_Name, image):     
        gbk_Name = self._prepare_window_name(window_Name)
        
        #窗口大小可调整
        cv2.namedWindow(gbk_Name, cv2.WINDOW_NORMAL)
        cv2.resizeWindow(gbk_Name, *self.default_window_size)
        cv2.imshow(gbk_Name, image)
        print(f"请点击图像窗口获得焦点, 再按任意键关闭 '{window_Name}' 窗口...")
        
        #等待用户按键，0表示无限等待直至用户按下任意键
        cv2.waitKey(0)
        cv2.destroyWindow(gbk_Name)

    """读取图像"""
    def read_image(self, image_Path):
        #检查文件是否存在
        if not os.path.exists(image_Path):
            print(f"错误: 文件 '{image_Path}' 不存在")
            return None
        
        #检查文件格式是否支持
        file_Ext = os.path.splitext(image_Path)[1].lower()
        if file_Ext not in self.supported_formats:
            print(f"错误: 不支持的图像格式 '{file_Ext}'")
            return None
        
        #读取图像
        try:
            image = cv2.imread(image_Path)
            if image is None:
                print(f"错误: 无法读取图像文件 '{image_Path}'")
                return None
            print(f"成功读取图像，形状: {image.shape}")
            #print(image.dtype)
            return image
        except Exception as e:
            print(f"读取图像时发生错误: {str(e)}")
            return None

    """显示图像"""
    def show_image(self, image):
        if image is None:
            print("图像数据为空")
            return
        
        #判断是彩色图像还是灰度图像
        window_Name = ''
        if len(image.shape) == 3:
            window_Name = '彩色图像'
        else:
            window_Name = '灰度图像'
        
        #显示图像
        self._create_window(window_Name, image)

    """转换为灰度图像"""
    def to_grayscale_image(self, image):
        if image is None:
            print("错误: 图像数据为空")
            return 
        
        #如果图像是彩色，就转换为灰度图
        if len(image.shape) == 3:
            gray_Image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        else:
            gray_Image = image
        
        return gray_Image

    """显示单波段图像"""
    def show_single_band(self, image, band_Index, window_Name='单波段图像'):
        if image is None:
            print("错误: 图像数据为空")
            return
        
        #检查图像是否为彩色图像
        if len(image.shape) != 3:
            print("错误: 输入图像不是彩色图像,无法提取单波段")
            return
        
        #检查波段索引是否有效
        if band_Index < 0 or band_Index >2:
            print("波段索引无效,应在0-2范围内")
            return 
        
        #创建一个与原图大小相同的单波段图像
        single_Band = np.zeros_like(image)
        
        #只保留指定波段的信息
        single_Band[:,:,band_Index] = image[:,:,band_Index]
        
        #显示单波段图像
        display_Name = f"{window_Name} - {self.band_names[band_Index]}"
        self._create_window(display_Name, single_Band)

    """计算协方差矩阵(用定义)"""
    def calculate_covariance_matrix(self, image):
        if image is None:
            print("错误: 图像数据为空")
            return
        
        #检查图像是否为多波段图像，否则无法进行计算
        if len(image.shape) <= 2:
            print("错误: 输入的图像不是多波段图像,无法计算波段间协方差")
            return None
        
        #获取图像的波段数和像素总数
        num_Bands = image.shape[2]
        height, width = image.shape[0], image.shape[1]
        num_Pixels = height * width
        
        #初始化协方差矩阵
        cov_Matrix = np.zeros(shape=(num_Bands, num_Bands))
        
        #计算每个波段的均值
        means = np.mean(image, axis=(0, 1))
        
        #计算每两个波段之间的协方差（使用无偏估计）
        for i in range(num_Bands):
            for j in range(num_Bands):
                #中心化处理
                centered_I = image[:,:,i] - means[i]
                centered_J = image[:,:,j] - means[j]
                #计算协方差（除以n-1得到无偏估计）
                cov_Matrix[i, j] = np.sum(centered_I * centered_J) / (num_Pixels - 1)
        return cov_Matrix

    """计算协方差矩阵(调用cov函数)"""
    def calculate_covariance_matrix_2(self, image):
        if image is None:
            print("错误: 图像数据为空")
            return
        
        #检查图像是否为多波段图像，否则无法进行计算
        if len(image.shape) <= 2:
            print("错误: 输入的图像不是多波段图像,无法计算波段间协方差")
            return None
        
        #获取图像的波段数和像素总数
        num_Bands = image.shape[2]
        height, width = image.shape[0], image.shape[1]
        num_Pixels = height * width
        
        #创建一个按波段展平的数组
        flatten_Image = np.zeros(shape=(num_Bands, num_Pixels))
        
        #展平每一个波段
        for i in range(num_Bands):
            flatten_Image[i] = image[:,:,i].flatten()
        
        #计算协方差矩阵
        cov_Mat = np.cov(flatten_Image)
        return cov_Mat

    """生成每个波段的直方图"""
    def generate_band_histograms(self, image, show_Plot=True, save_Path=None):
        if image is None:
            print("错误: 图像数据为空")
            return None
 
        num_Bands = 0
        #检查图像是否为多波段图像
        if len(image.shape) != 3:
            num_Bands = 1
        else:
            #获取图像波段数
            num_Bands = image.shape[2]

        #创建一个包含所有波段直方图的图像
        plt.figure(figsize=(15, 5))

        #生成每个波段的直方图
        histograms = []
        for i in range(num_Bands):
            #提取当前波段
            band = image
            if len(image.shape) == 3:
                band = image[:,:,i]
            #计算直方图
            hist = cv2.calcHist([band], [0], None, [256], [0, 256])
            histograms.append(hist)
            #绘制直方图
            plt.subplot(1, num_Bands, i+1)
            #将hist转换为一维数组并展平,然后使用plt.hist绘制直方图
            if num_Bands == 1:
                plt.hist(band.ravel(), 256, range=[0, 256], color='gray', alpha=0.7)
                plt.title(f'灰度直方图')
            else:
                plt.hist(band.ravel(), 256, range=[0, 256], color=self._get_band_color(i), alpha=0.7)
                plt.title(f'{self.band_names[i]}波段直方图')
            plt.xlabel('像素值')
            plt.ylabel('像素数量')
            plt.xlim([0, 256])
        plt.tight_layout()

        #保存直方图图像
        if save_Path:
            try:
                #检查save_Path是否为目录
                if os.path.isdir(save_Path) or save_Path.endswith('/') or save_Path.endswith('\\'):
                    #如果是目录，提示用户输入文件名（不包括扩展名，默认保存为png格式）
                    filename = input("请输入保存的文件名(不包括扩展名,默认保存为png格式): ")
                    #如果文件名没有扩展名，添加.png扩展名
                    if not os.path.splitext(filename)[1]:
                        filename += '.png'
                    save_Path = os.path.join(save_Path, filename)
                #确保保存目录存在
                os.makedirs(os.path.dirname(os.path.abspath(save_Path)), exist_ok=True)
                #保存图像
                plt.savefig(save_Path)
                print(f"直方图已保存到: {save_Path}")
            except Exception as e:
                print(f"保存直方图时发生错误: {str(e)}")

        #显示直方图
        if show_Plot:
            plt.show()
        return histograms
        
    """根据波段索引获取对应的颜色"""
    def _get_band_color(self, band_Index):
        # 为不同波段设置不同的颜色
        colors = ['blue', 'green', 'red']
        if band_Index < len(colors):
            return colors[band_Index]
        else:
            return 'black'

    """OTSU大津法分割灰度图像"""
    def otsu(self, gray_Image, save_Path=None):
        #确认是否真为灰度图像
        if len(gray_Image.shape) == 3:
            print("错误: 输入的图像不是灰度图像,无法使用OTSU大津法分割")
            return None

        #计算阈值
        perfect_Thresh_List = np.zeros(256)
        for threshold in range(256):
            #数组if_Big元素类型为bool,用于判断各像元值是不是当前选定的阈值
            if_Big = gray_Image > threshold
            #计算前景像元比例与背景像元比例
            p1 = np.sum(if_Big) / gray_Image.size
            p2 = 1 - p1
            #计算总像元均值、前景像元均值与背景像元均值
            m = np.mean(gray_Image)
            m1 = np.mean(gray_Image[if_Big]) if p1 > 0 else 0
            m2 = np.mean(gray_Image[~if_Big]) if p2 > 0 else 0
            #计算类间方差
            variance = p1 * ((m1 - m) ** 2) + p2 * ((m2 - m) ** 2)
            #加入阈值表
            perfect_Thresh_List[threshold] = variance
        
        #找到最大类间方差对应的阈值
        best_Threshold = np.argmax(perfect_Thresh_List)
        
        #对原图像进行分割：大于阈值的像素设为255（白色），小于等于阈值的像素设为0（黑色）
        segmented_Image = np.where(gray_Image > best_Threshold, 255, 0).astype(np.uint8)
        
        #绘制原始灰度图像和分割后的图像
        plt.figure(figsize=(12, 6))
        
        #显示原始灰度图像
        plt.subplot(1, 2, 1)
        plt.imshow(gray_Image, cmap='gray')
        plt.title('原始灰度图像')
        plt.axis('off')
        
        #显示分割后的图像
        plt.subplot(1, 2, 2)
        plt.imshow(segmented_Image, cmap='gray')
        plt.title(f'OTSU分割结果 (阈值={best_Threshold})')
        plt.axis('off')
        
        plt.tight_layout()
        
        #保存图像
        if save_Path:
            try:
                #检查save_Path是否为目录
                if os.path.isdir(save_Path) or save_Path.endswith('/') or save_Path.endswith('\\'):
                    #如果是目录，提示用户输入文件名（不包括扩展名，默认保存为png格式）
                    filename = input("请输入保存的文件名(不包括扩展名,默认保存为png格式): ")
                    #如果文件名没有扩展名，添加.png扩展名
                    if not os.path.splitext(filename)[1]:
                        filename += '.png'
                    save_Path = os.path.join(save_Path, filename)
                #确保保存目录存在
                os.makedirs(os.path.dirname(os.path.abspath(save_Path)), exist_ok=True)
                #保存图像
                plt.savefig(save_Path)
                print(f"OTSU分割图已保存到: {save_Path}")
            except Exception as e:
                print(f"保存OTSU分割图时发生错误: {str(e)}")
        
        #显示图像
        plt.show()
        
        return best_Threshold, segmented_Image

    """改进型OTSU(局部自适应OTSU)"""
    def local_adaptive_otsu(self, gray_Image, save_Path=None):
        if gray_Image is None:
            print("错误: 输入图像为空")
            return None
        
        #检查是否为灰度图像
        if len(gray_Image.shape) == 3:
            print("错误: 输入的图像不是灰度图像,需要先转换为灰度图像")
            return None
        
        #获取图像尺寸
        height, width = gray_Image.shape
        
        #计算每块的大小，确保能够均匀分割且不遗漏像元
        block_height = height // 4
        block_width = width // 4
        
        #计算余数，用于处理不能被4整除的情况
        height_remainder = height % 4
        width_remainder = width % 4
        
        #存储分割后的原始图像块
        blocks = []
        #存储分割后的位置信息，用于拼接
        block_positions = []
        
        #分割图像为4x4=16块
        for i in range(4):
            for j in range(4):
                #计算当前块的起始和结束位置
                start_y = i * block_height
                #处理高度方向的余数，确保不遗漏像元
                if i < height_remainder:
                    end_y = start_y + block_height + 1
                else:
                    end_y = start_y + block_height
                
                start_x = j * block_width
                #处理宽度方向的余数，确保不遗漏像元
                if j < width_remainder:
                    end_x = start_x + block_width + 1
                else:
                    end_x = start_x + block_width
                
                #提取当前块
                block = gray_Image[start_y:end_y, start_x:end_x]
                blocks.append(block)
                #记录块的位置信息
                block_positions.append((start_y, end_y, start_x, end_x))
         
        #创建一个空白图像用于存储拼接结果
        segmented_image = np.zeros((height, width), dtype=np.uint8)
        
        #存储每个块的阈值
        thresholds = []
        
        #对16块分别进行传统OTSU算法
        for i in range(16):
            #对每个块应用otsu算法，不显示图像
            best_threshold, seg_block = self.otsu(blocks[i], None)
            thresholds.append(best_threshold)
            
            #获取该块的位置信息
            start_y, end_y, start_x, end_x = block_positions[i]
            
            #将处理后的块放回原位置
            segmented_image[start_y:end_y, start_x:end_x] = seg_block
        
        #计算平均阈值
        avg_threshold = sum(thresholds) / len(thresholds)
        print(f"各块阈值范围: {min(thresholds)} - {max(thresholds)}")
        print(f"平均阈值: {avg_threshold:.2f}")
        
        #绘制原始灰度图像和局部自适应OTSU分割后的图像
        plt.figure(figsize=(12, 6))
        
        #显示原始灰度图像
        plt.subplot(1, 2, 1)
        plt.imshow(gray_Image, cmap='gray')
        plt.title('原始灰度图像')
        plt.axis('off')
        
        #显示局部自适应OTSU分割后的图像
        plt.subplot(1, 2, 2)
        plt.imshow(segmented_image, cmap='gray')
        plt.title('局部自适应OTSU分割结果')
        plt.axis('off')
        
        plt.tight_layout()
        
        #保存图像
        if save_Path:
            try:
                #检查save_Path是否为目录
                if os.path.isdir(save_Path) or save_Path.endswith('/') or save_Path.endswith('\\'):
                    #如果是目录，提示用户输入文件名（不包括扩展名，默认保存为png格式）
                    filename = input("请输入保存的文件名(不包括扩展名,默认保存为png格式): ")
                    #如果文件名没有扩展名，添加.png扩展名
                    if not os.path.splitext(filename)[1]:
                        filename += '.png'
                    save_Path = os.path.join(save_Path, filename)
                #确保保存目录存在
                os.makedirs(os.path.dirname(os.path.abspath(save_Path)), exist_ok=True)
                #保存图像
                plt.savefig(save_Path)
                print(f"局部自适应OTSU分割图已保存到: {save_Path}")
            except Exception as e:
                print(f"保存局部自适应OTSU分割图时发生错误: {str(e)}")
        
        #显示图像
        plt.show()
        
        return avg_threshold, segmented_image

if __name__ == "__main__":
    #创建图像处理器实例
    processor = image_Processor_OpenCV()

    #测试图像路径1：D:\Files\Code_Work_Space\Pattern recongnition course codes\Image classfication\Treshhold value method\test_images\zhuozi.jpg
    #测试图像路径2：D:\Files\Code_Work_Space\Pattern recongnition course codes\Image classfication\Treshhold value method\test_images\wyzg.jpg
    #测试图像路径3：D:\Files\Code_Work_Space\Pattern recongnition course codes\Image classfication\Treshhold value method\test_images\shenbaoshu.jpg

    #获取用户输入的图像路径
    image_Path = input("请输入图像文件路径: ")

    #读取图像
    image = processor.read_image(image_Path)

    """
    #测试显示图像功能
    #彩色
    processor.show_image(image)
    #转换为灰度图像
    g_Image = processor.to_grayscale_image(image)
    #灰度
    processor.show_image(g_Image)
    #按波段
    for i in range(3):
        processor.show_single_band(image, i)
    """
    """
    #测试协方差矩阵计算
    cov_Matrix_1 = processor.calculate_covariance_matrix(image)
    cov_Matrix_2 = processor.calculate_covariance_matrix_2(image)
    print(f"协方差矩阵（定义法）：")
    print(cov_Matrix_1)
    print(f"协方差矩阵（cov函数）：")
    print(cov_Matrix_2)
    """

    #获取用户保存图像的路径
    save_Image_Path = input("请输入图像保存路径: ")
    if not save_Image_Path:  #当用户直接按Enter键不输入任何内容时
        save_Image_Path = "D:/Files/Code_Work_Space/Pattern recongnition course codes/Image classfication/Treshhold value method/test_save/"
    
    #转换为灰度图像
    g_Image = processor.to_grayscale_image(image)
    
    #显示三波段直方图
    #processor.generate_band_histograms(image, True, save_Image_Path)
    #显示灰度直方图
    #processor.generate_band_histograms(g_Image, True, save_Image_Path)
    
    #调用otsu方法进行分割并保存结果
    #best_Threshold, segmented_Image = processor.otsu(g_Image, save_Image_Path)
    #print(f"OTSU最佳阈值: {best_Threshold}")
    
    #调用局部自适应OTSU进行分割并保存结果
    l_A_Threshold, l_A_Seg_Image = processor.local_adaptive_otsu(g_Image, save_Image_Path)
    