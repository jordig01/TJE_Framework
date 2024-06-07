varying vec3 v_world_position;
varying vec3 v_normal;
varying vec2 v_uv;

uniform vec4 u_background_color;
uniform vec3 u_camera_position;
uniform vec3 u_ambient_light;
uniform vec3 u_light_color;
uniform vec3 u_light_position;
uniform float u_fog_factor;

uniform float u_tiling;

uniform vec3 u_Ka;
uniform vec3 u_Kd;
unifrom vec3 u_Ks;

uniform sampler2D u_texture;
uniform sampler2D u_normals_texture;
uniform vec2 u_maps;

mat3 cotangent_frame(vec3 N, vec3 p, vec2 uv){
	// get edge vectors of the pixel triangle
	vec3 dp1 = dFdx( p );
	vec3 dp2 = dFdy( p );
	vec2 duv1 = dFdx( uv );
	vec2 duv2 = dFdy( uv );

	// solve the linear system
	vec3 dp2perp = cross( dp2, N );
	vec3 dp1perp = cross( N, dp1 );
	vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
	vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;

	// construct a scale-invariant frame
	float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
	return mat3( T * invmax, B * invmax, N );
}

vec3 perturbNormal( vec3 N, vec3 V, vec2 texcoord, vec3 normal_pixel ){

	// assume N, the interpolated vertex normal and
	// V, the view vector (eye to vertex)
	normal_pixel = normal_pixel * 255./127. - 128./127.;
	mat3 TBN = cotangent_frame(N, V, texcoord);
	return normalize(TBN * normal_pixel);
}


vec4 applyLight()
{
    vec4 Kd = vec4(u_Kd, 1.0);

    if(u_maps.x){
        Kd = texture2D(u_texture, v_uv);
    }

    vec3 L = normalize(u_light_position - v_world_position);
    vec3 V = normalize(u_camera_position - v_world_position);
    vec3 N = normalize(v_normal);


    if(u_maps.y){
        vec3 normals_texture = texture2D(u_normals_texture, v_uv);
        N = perturbNormal(N, V, v_uv, normals_texture);
    }

    vec3 ambient = u_Ka * Kd;

    float NdotL = max(0.0, dot(L,N));
    vec3 diffuse = Kd * u_light_color * NdotL;

    vec3 R = reflect(-L, N);
    float RdotV = pow(max(0.0, dot(R,V)), 20);
    vec3 specular = u_Ks * u_light_color * RdotV;

    vec3 total_light = ambient + diffuse + specular;

    return vec4(total_light, Kd.a)
}

void main(){
    vec4 final_color = applyLight();

    //float dist = length(u_camera_position - v_world_position);

    gl_FragColor = final_color;

}