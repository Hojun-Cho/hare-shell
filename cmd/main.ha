use os;
use fmt;

export fn main() void = {
	let envs:[] str= os::getenvs();
	for (let i = 0z; i < len(envs); i += 1) {
		fmt::println(envs[i])!;
	};
};
