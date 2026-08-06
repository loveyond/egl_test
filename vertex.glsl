/*
	OpenGL ES 顶点着色器（Vertex Shader）: 把输入的顶点坐标，直接交给 OpenGL 的绘制流水线
	它决定三角形/矩形画在哪里

	还告诉后面的fragment：这个位置对应图片哪里
*/


/*
	定义一个叫 position 的变量，它来自 CPU 端传入
		attribute: 表示这个数据是每个顶点自己的属性
			比如：一个三角形有3个顶点：
					float vertices[] =
					{
					    -0.5, -0.5, 0.0,   // 顶点1
					     0.5, -0.5, 0.0,   // 顶点2
					     0.0,  0.5, 0.0    // 顶点3
					};
				CPU把这些数据传给GPU，GPU每处理一个顶点，就会调用一次main()，
					第一次： position=(-0.5,-0.5,0)
					第二次： position=(0.5,-0.5,0)
					第三次： position=(0,0.5,0)
		vec3: 表示：3个float组成的向量	
*/

attribute vec3 position;

/*
    MVP
	mat4 4×4矩阵	
	uniform 所有顶点、所有片元共享的一份数据。
	vec4 4个浮点数
*/
uniform mat4 MVP;

// uniform vec2 offset;

// attribute vec2 texCoord;

// varying vec2 vTexCoord;



// 每一个顶点都会进入这里
void main()
{
	/*
		相当于：
		vec4(
		    position.x,
		    position.y,
		    position.z,
		    1.0
		)
		输入：position=(-0.5,-0.5,0)
		然后：gl_Position=(-0.5,-0.5,0,1.0)
						x=-0.5
						y=-0.5
						z=0
						w=1.0
	*/

	gl_Position = MVP * vec4(position,1.0);
	
//    gl_Position = vec4( position, 1.0 );

//    gl_Position = vec4( position.x + offset.x,
//			            position.y + offset.y,
//			            position.z,
//			            1.0 );


//    vTexCoord = texCoord;
    
}

