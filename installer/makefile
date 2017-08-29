SRC_ROOT=..
BUILD_ROOT=$(SRC_ROOT)/Builds/MacOSX
PRODUCTS_ROOT=$(BUILD_ROOT)/build/Release

PRODUCT_NAME=ChuckRacks
PRODUCT_VERSION=1.0
INSTALLER=$(PRODUCT_NAME)-$(PRODUCT_VERSION).pkg

XCODE_PROJECT=ChuckRacks.xcodeproj
XCODE_TARGET_VST="ChuckRacks - VST"
XCODE_TARGET_AU="ChuckRacks - AU"
XCODE_CONFIGURATION=Release

PLUGIN_VST=$(PRODUCT_NAME).vst
PLUGIN_AU=$(PRODUCT_NAME).component

VST_PKG=$(PLUGIN_VST).pkg
AU_PKG=$(PLUGIN_AU).pkg
PLUGIN_PKGS=$(VST_PKG) $(AU_PKG)

VST_DIR=/Library/Audio/Plug-Ins/VST
AU_DIR=/Library/Audio/Plug-Ins/Components

IDENTIFIER_BASE=edu.calarts.mtiid
CERT?=Developer ID Installer: Spencer Salazar (9GU9FHJ3JC)
ifneq ($(CERT),)
OPTION_SIGNING=--sign "$(CERT)"
endif

.PHONY: all clean clean-au clean-vst
all: $(INSTALLER)

$(INSTALLER): $(PLUGIN_PKGS) Distribution.xml
	@echo "--- Creating installer ---"
ifeq ($(OPTION_SIGNING),)
	@echo "warning: skipping code signing"
endif
	productbuild --distribution Distribution.xml --version $(PRODUCT_VERSION) --package-path . $(OPTION_SIGNING) --resources resources $@

$(VST_PKG): %.pkg: %
	rm -rf $<.tmp/$(VST_DIR)
	mkdir -p $<.tmp/$(VST_DIR)
	cp -afRL $< $<.tmp/$(VST_DIR)
	pkgbuild --root $<.tmp --identifier $(IDENTIFIER_BASE).$(basename $<) $@
	rm -rf $<.tmp

$(AU_PKG): %.pkg: %
	rm -rf $<.tmp/$(AU_DIR)
	mkdir -p $<.tmp/$(AU_DIR)
	cp -afRL $< $<.tmp/$(AU_DIR)
	pkgbuild --root $<.tmp --identifier $(IDENTIFIER_BASE).$(basename $<) $@
	rm -rf $<.tmp

$(PLUGIN_VST):
	xcodebuild -project $(BUILD_ROOT)/$(XCODE_PROJECT)/ -target $(XCODE_TARGET_VST) -configuration $(XCODE_CONFIGURATION)
	rm -rf $(PLUGIN_VST)
	cp -afRL $(PRODUCTS_ROOT)/$(PLUGIN_VST) .
	touch $@

$(PLUGIN_AU):
	xcodebuild -project $(BUILD_ROOT)/$(XCODE_PROJECT)/ -target $(XCODE_TARGET_AU) -configuration $(XCODE_CONFIGURATION)
	rm -rf $(PLUGIN_AU)
	cp -afRL $(PRODUCTS_ROOT)/$(PLUGIN_AU) .
	touch $@

clean:
	rm -rf $(PLUGINS) $(PLUGIN_PKGS) $(INSTALLER)

clean-vst:
	xcodebuild clean -project $(BUILD_ROOT)/$(XCODE_PROJECT)/ -target $(XCODE_TARGET_VST) -configuration $(XCODE_CONFIGURATION)

clean-au:
	xcodebuild clean -project $(BUILD_ROOT)/$(XCODE_PROJECT)/ -target $(XCODE_TARGET_AU) -configuration $(XCODE_CONFIGURATION)

clean-all: clean clean-vst clean-au
	