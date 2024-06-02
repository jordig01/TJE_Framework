#include "entityMesh.h"


enum eButtonId{
	PlayButton,
	ExitButton,
	RestartButton,
	UndefinedButton
};

class EntityUI : public EntityMesh {
	public:

		EntityUI(Vector2 size, const Material& material);
		EntityUI(Vector2 pos, Vector2 size, const Material& material, eButtonId button_id = UndefinedButton);
		~EntityUI() {};

		Vector2 position;
		Vector2 size;

		bool visible = true;
		float mask;


		Texture* original_texture;
		Texture* hover_texture;

		//3D HUD
		bool is3D = false;
		Vector3 pos3d;

		eButtonId button_id;

		void render(Camera* camera);
		void update(double seconds_elapsed);
		void update3D(Vector3 position3d);
};