# 최종 실행파일명
TARGET = ledtest_lib buttontest_lib buzzertest_lib fndtest_lib textlcdtest_lib \
         colorledtest_lib temperaturetest_lib accelMagGyrotest_lib

# 크로스 컴파일러 설정
CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

# 라이브러리 및 오브젝트
LIB = libMyPeri.a
OBJS = led.o button.o buzzer.o fnd.o textlcd.o colorled.o temperature.o accelMagGyro.o
SRCS = led.c led.h button.c button.h buzzer.c buzzer.h \
       fnd.c fnd.h textlcd.c textlcd.h colorled.c colorled.h \
       temperature.c temperature.h accelMagGyro.c accelMagGyro.h \
       ledtest_lib.c buttontest_lib.c buzzertest_lib.c fndtest_lib.c \
       textlcdtest_lib.c colorledtest_lib.c temperaturetest_lib.c accelMagGyrotest_lib.c

all: $(TARGET)

# 라이브러리 생성
$(LIB): $(OBJS)
   $(AR) rc $(LIB) $(OBJS)

# 오브젝트 파일 만들기
led.o: led.c led.h
   $(CC) -c led.c -o led.o

button.o: button.c button.h
   $(CC) -c button.c -o button.o

buzzer.o: buzzer.c buzzer.h
   $(CC) -c buzzer.c -o buzzer.o

fnd.o: fnd.c fnd.h
   $(CC) -c fnd.c -o fnd.o

textlcd.o: textlcd.c textlcd.h
   $(CC) -c textlcd.c -o textlcd.o

colorled.o: colorled.c colorled.h
   $(CC) -c colorled.c -o colorled.o

temperature.o: temperature.c temperature.h
   $(CC) -c temperature.c -o temperature.o

accelMagGyro.o: accelMagGyro.c accelMagGyro.h
   $(CC) -c accelMagGyro.c -o accelMagGyro.o

# 실행파일 만들기 (라이브러리 링크)
ledtest_lib: ledtest_lib.c $(LIB)
   $(CC) ledtest_lib.c -L. -lMyPeri -o ledtest_lib

buttontest_lib: buttontest_lib.c $(LIB)
   $(CC) buttontest_lib.c -L. -lMyPeri -lpthread -o buttontest_lib

buzzertest_lib: buzzertest_lib.c $(LIB)
   $(CC) buzzertest_lib.c -L. -lMyPeri -lpthread -o buzzertest_lib

fndtest_lib: fndtest_lib.c $(LIB)
   $(CC) fndtest_lib.c -L. -lMyPeri -o fndtest_lib

textlcdtest_lib: textlcdtest_lib.c $(LIB)
   $(CC) textlcdtest_lib.c -L. -lMyPeri -o textlcdtest_lib

colorledtest_lib: colorledtest_lib.c $(LIB)
   $(CC) colorledtest_lib.c -L. -lMyPeri -o colorledtest_lib

temperaturetest_lib: temperaturetest_lib.c $(LIB)
   $(CC) temperaturetest_lib.c -L. -lMyPeri -o temperaturetest_lib

accelMagGyrotest_lib: accelMagGyrotest_lib.c $(LIB)
   $(CC) accelMagGyrotest_lib.c -L. -lMyPeri -o accelMagGyrotest_lib

# 청소
clean:
   rm -f *.o *.a $(TARGET)
