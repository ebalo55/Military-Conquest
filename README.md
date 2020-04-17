# MilitaryConquest
Run:
```bash
cmake CMakeLists.txt
make 
```

In order to run the tests (after running make):
```bash
cd Tests
./test
```

This program requires libSFML version 2 and nlohmann-json v3 library.

Most of the behaviour of the game si customizable using the `config.json` file located under `Assets` and
the two map configuration file `easy.map` and `hard.map` both under the same directory of the configuration
file.

## Config.json global structure:
- [window](#window)
    - width
    - height
- enemies
    - tile-name
    - types
    - enemy-wave-template
    - boss-wave-template
- turrets
    - tile-name
    - types
- achievements

### Window
