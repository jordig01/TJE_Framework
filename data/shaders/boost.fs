varying vec2 v_uv;

uniform vec4 u_color;
uniform float u_boost;

void main()
{
    vec3 final_color;
    if(v_uv.y > u_boost * 0.001){
        final_color = vec3(0.1,0.1, 0.1);
    }else{
        final_color = vec3(0, 0, 1);
    }

    gl_FragColor = vec4(final_color*u_color.rgb, 1.0);
}
