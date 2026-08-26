
CROSS_COMPILE = aarch64-linux-gnu-

CXX = $(CROSS_COMPILE)g++

TARGET = egl_test

CXXFLAGS = -I. -I../t507_gpu/include -I./cameraV4L2 -DEGL_FBDEV=1 -std=c++11

LDFLAGS = -L../t507_gpu/lib

LIBS = -lEGL -lGLESv2


SRCS = main.cpp GLRenderer.cpp Matrix4.cpp Sprite.cpp Mesh.cpp EGLManager.cpp Shader.cpp Texture.cpp \
		CameraEngine.cpp cameraV4L2/CameraV4L2.cpp cameraV4L2/image_converter.cpp YUVTexture.cpp

OBJS = $(SRCS:.cpp=.o)


$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) $(LIBS) -o $(TARGET)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(TARGET)


