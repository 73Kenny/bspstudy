#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x19fdd0c3, "module_layout" },
	{ 0x5d581c1c, "input_unregister_device" },
	{ 0xc09265b4, "input_free_device" },
	{ 0x64453d4a, "input_register_device" },
	{ 0xdab60f19, "input_set_capability" },
	{ 0x96450829, "misc_deregister" },
	{ 0xae4f88c7, "devm_input_allocate_device" },
	{ 0x3fff8891, "misc_register" },
	{ 0x51439fc2, "input_event" },
	{ 0xc5850110, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "4CCBCFC022CCD4C765D4670");
