import cv2
import os
try:
    from PIL import Image
except ImportError:
    import Image
import pytesseract

# 설치한 tesseract 프로그램 경로 (64비트)
pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract'
# 32비트인 경우 => r'C:\Program Files (x86)\Tesseract-OCR\tesseract'

# 이미지 불러오기, Gray 프로세싱
image = cv2.imread("image2.png")
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# write the grayscale image to disk as a temporary file so we can
# 글자 프로세싱을 위해 Gray 이미지 임시파일 형태로 저장.
filename = "{}.png".format(os.getpid())
cv2.imwrite(filename, gray)

# Simple image to string
text = pytesseract.image_to_string(Image.open(filename), lang=None)
#text = pytesseract.image_to_string(Image.open(filename), lang='kor')
os.remove(filename)

print("이미지 숫자 검출 결과 : " + text)

cv2.imshow("Image", image)
cv2.waitKey(0)