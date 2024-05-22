

enum eButtonId{
	PlayButton,
	ExitButton
	//...
};

	class EntityUI : public EntityMesh {
	public:

		EntityUI(Vector2 size, const Material& material);
		EntityUI(Vector2 pos, Vector2 size, const Material& material, eButtonId button_id = UndefinedButton, );
		EntityUI();
};