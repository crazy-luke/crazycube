#include "volume_bar.h"

#include <WString.h>

#include "gui/gui.h"
#include "framework/system/speaker.h"

void VolumeBar::ShowVolumeBar(uint8_t volume){
    if(!ui_volumebar_exist()){
        ui_init_volumebar();
        delete_volumebar(1000);
    }
    int value = map(volume,0,MAX_VOLUME,0,100);
    update_volumebar(value);
    update_volumebar_labe(String(value).c_str());
}