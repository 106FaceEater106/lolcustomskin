#include <cstdio>
#include <stdexcept>
#include "modremap.hpp"


int main() {
    puts("Source: https://github.com/moonshadow565/lolskinmod");
    puts("WIP Warning: This is alternative approach to patching the game.");
    puts("=============================================================");
    ModRemap::Config config = {};
    config.load();
    config.print();

    try {
        for(;;) {
            puts("=============================================================");
            puts("Waiting for league to start...");
            auto process = Process("League of Legends.exe", 100);
            if(config.good(process)) {
                puts("Early patching...");
                config.patch(process);
            } else {
                puts("Updating offsets...");
                if(config.rescan(process)) {
                    config.save();
                    config.print();
                    puts("Late patching...");
                    config.patch(process);
                } else {
                    throw std::runtime_error("Failed to fetch offsets!");
                }
            }
            puts("Wating for league to exit...");
            process.WaitExit(15000);
        }
    } catch(std::exception const& err) {
        puts("Error: ");
        puts(err.what());
        puts("Press enter to exit...");
        getc(stdin);
    }
}
