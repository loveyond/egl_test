// OpenGL ES 片元着色器（Fragment Shader，也叫像素着色器）
// 它决定每一个像素显示什么颜色

/*
	指定float精度：
		lowp       低精度
		mediump    中等精度
		highp      高精度
*/

precision mediump float;

/*
	uniform 所有顶点、所有片元共享的一份数据。
	vec4 4个浮点数
*/
uniform vec4 color;

// uniform sampler2D texture;


/*
	varying shader之间 插值传递 纹理坐标
*/
// varying vec2 vTexCoord;



/*
	lcd分辨率：1024*600
		1024 × 600 = 614400个像素
		GPU会执行这个 fragment shader 大约60万个次
*/

void main()
{
	/*
		R	红
		G	绿
		B	蓝
		A	透明度
	*/

//    gl_FragColor = vec4( 1.0, 0.0, 0.0, 1.0 );

	gl_FragColor = color;

	//当前像素 去texture里面取颜色
//	gl_FragColor = texture2D(texture,vTexCoord);
    
}

