varying vec2 v_uv;

uniform vec4 u_color;
uniform float u_boost;

void main()
{
	gl_FragColor = vec4(0, 0, v_uv.y * u_boost, 1);
}
