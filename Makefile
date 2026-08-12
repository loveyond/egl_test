
CROSS_COMPILE = aarch64-linux-gnu-

CXX = $(CROSS_COMPILE)g++

TARGET = egl_test

CXXFLAGS = -I../t507_gpu/include -DEGL_FBDEV=1

LDFLAGS = -L../t507_gpu/lib

LIBS = -lEGL -lGLESv2


SRCS = main.cpp GLRenderer.cpp Matrix4.cpp Sprite.cpp Mesh.cpp EGLManager.cpp Shader.cpp Texture.cpp

OBJS = $(SRCS:.cpp=.o)


$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) $(LIBS) -o $(TARGET)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(TARGET)


