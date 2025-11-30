//==============================================================
// Custom script command: specialeffect3
// Uso em script:
//
//   specialeffect3 <gid>, <effect_id>{, <target>};
//
// Exemplo:
//   specialeffect3 .@gid, EF_ENERGYCOAT, AREA;
//==============================================================

BUILDIN_FUNC(specialeffect3)
{
	int id   = script_getnum(st, 2); // GID (mob, player, etc.)
	int type = script_getnum(st, 3); // Effect ID (EF_*)
	enum send_target target;

	if (script_hasdata(st, 4))
		target = (enum send_target)script_getnum(st, 4);
	else
		target = AREA;

	struct block_list *bl = map_id2bl(id);
	if (bl == NULL) {
		ShowError("buildin_specialeffect3: unknown game object with id %d.\n", id);
		return SCRIPT_CMD_FAILURE;
	}

	if (type <= EF_NONE || type >= EF_MAX) {
		ShowError("buildin_specialeffect3: unsupported effect id %d.\n", type);
		return SCRIPT_CMD_FAILURE;
	}

	if (target == SELF) {
		struct map_session_data *sd = NULL;
		if (!script_rid2sd(sd) || sd == NULL)
			return SCRIPT_CMD_FAILURE;
		clif_specialeffect_single(bl, type, sd->fd);
	} else {
		clif_specialeffect(bl, type, target);
	}

	return SCRIPT_CMD_SUCCESS;
}
