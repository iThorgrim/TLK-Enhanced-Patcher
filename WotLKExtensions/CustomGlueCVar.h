#pragma once

#include "SharedDefines.h"

class Main;

// CVar flags (based on analysis of FUN_00767fc0 calls)
enum CVarFlags : uint32_t
{
	CVAR_FLAG_NONE          = 0x0,
	CVAR_FLAG_ARCHIVE       = 0x1,  // Saved to config.wtf
	CVAR_FLAG_READONLY      = 0x2,  // Cannot be changed by user
	CVAR_FLAG_GLUE          = 0x4,  // Available in GlueXML (login/character select)
	CVAR_FLAG_CHEAT         = 0x8,  // Requires GM access
};

// Structure representing a CVar to be registered
struct CustomCVarEntry
{
	const char* name;
	const char* description;
	const char* defaultValue;
	void* callback;
	uint32_t flags;
};

class CustomGlueCVar
{
public:
	// Register a custom CVar for GlueXML
	static void* RegisterGlueCVar(
		const char* name,
		const char* description,
		const char* defaultValue,
		void* callback = nullptr,
		uint32_t flags = CVAR_FLAG_GLUE
	);

	// Add a CVar to the pending registration list
	static void AddCVar(const CustomCVarEntry& entry);

	// Get a registered CVar by name
	static void* GetCVar(const char* name);

	// Register all custom CVars (called internally before GlueXML loads)
	static void RegisterCustomCVars();

private:
	static void Apply();

	friend class Main;
};
