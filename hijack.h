#pragma once

namespace Hijack {
	BOOLEAN HijackViaHook(utils::Process &process, PVOID entry, LPCWSTR moduleName, LPCSTR functionName);
}