#ifndef %ENTITYNAME%_H
#define %ENTITYNAME%_H

class %ENTITYNAME% : computerScreen {
	using Screens;
	public:
		
		%ENTITYNAME%() {
			
		}
		
		~%ENTITYNAME%() {
			
		}
		
		void onInit() {
			super.onInit();
			createScreenWidget("%ENTITYNAME%/screen_info.xml");
			ScreenWidget _widget = getScreenWidget();
		}
		
		void onShutdown() {
			super.onShutdown();
		}
		
		void onUpdate() {
			super.onUpdate();
		}
		
		void onRender() {
			super.onRender();
		}
		
		void onFlush() {
			super.onFlush();
		}
};

#endif
