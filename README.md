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

This program requires libSFML version 2 and [nlohmann-json v3](https://github.com/nlohmann/json) library.

Most of the behaviour of the game si customizable using the `config.json` file located under `Assets` and
the two map configuration file `easy.map` and `hard.map` both under the same directory of the configuration
file.

## Config.json global structure:
- [window](#window)
    - width
    - height
- [enemies](#enemies)
    - tile-name
    - types
    - enemy-wave-template
    - boss-wave-template
- [turrets](#turrets)
    - tile-name
    - types
- [achievements](#achievements)

### Window
Property name | Property type | Default value
--- | :---: | ---
width | `int` | 1280
height | `int` | 800

Please consider that the standard turret and terrain sprites are 40x40px large while enemies are 20x20px large so if proportion
are respected the width and the height should always be a multiple of 40.
Please note that the width and height will resize the sole window to resize the map you should modify the file `easy.map` and `hard.map`

### Enemies
Property name | Property type | Default value
--- | :---: | ---
tile-name | `string` | enemy-tile-set.png
types | Array of objects | see [enemy type structure](#enemy-type-structure)
enemy-wave-template | Array of objects | see [enemy wave template](#enemy-wave-template)
boss-wave-template | Array of objects | see [enemy wave template](#enemy-wave-template)

##### Enemy type structure
The enemy options let you define the enemy number, type and characteristics.
Under the enemy you can also modify the wave number and type.

Property name | Property type | Explanation
--- | :---: | ---
identifier | `int` | A unique numeric identifier representing the instance of the enemy
tile-index | `int` | This value is used to clip a section of the tile and show it as the enemy sprite
boss | `bool` | A `true / false` value indicating whether the defined enemy should be considered as a boss or as a standard enemy
stats | Object | See single parameter specification
stats.hp | `int` | Numeric value representing the enemy health point
stats.velocity | `int` | Numeric value representing the enemy velocity, the suggested range vary from 35/40 to 200/250, values lower or higher may result in visual issues
stats.acceleration | `int` | Numeric value representing the enemy acceleration
stats.power | `int` | Numeric value representing the strength of the enemy this is used to compute the killing reward and the tower damages
stats.generation-time | Object | See single parameter specification
stats.generation-time.easy | `int` | Numeric value, specify the amount of time required to generate a single enemy during the easy game, ideally in bosses should be higher than in enemies
stats.generation-time.hard | `int` | Numeric value, specify the amount of time required to generate a single enemy during the hard and hacked game, ideally in bosses should be higher than in enemies
animated | `bool` or Object | This value is used as a conditional switch to animate or not the enemy sprite, if no animation is required the value must be set to `false`
animated.tile-index | `int` | Numeric value represent the second frame of the sprite animation
animated.frame-time | `int` | Numeric value representing the time between the two frames.<br>**This value is expressed in milliseconds**

##### Enemy wave template
Note that during the game a random number (between 1 and 3) of template is chosen and queued to generation.
Each used template will start the generation after a random number of milliseconds (between 1000 and 7500).
The possibility that different games follow the same wave generation pattern become smaller when the number of template grows.

Note that the standard enemy template and the boss template follows the same specification but ideally as the generation time of bosses
is higher than the one of the enemies if `timed` is set to `false` the number of generated bosses should be lesser than the one of the enemy
in order to don't create a never ending bosses wave

Property name | Property type | Explanation
--- | :---: | ---
timed | `bool` | A `true / false` switch indicating whether the associated amount represent the number of seconds after that the started generation stops or the real number of enemy instances to be generated.<br>Note that a timed template may generate one or more enemy less than the expected number depending on the screen refresh rate
amount | `int` | Numeric value representing the number of seconds the generation should last or the precise number of enemy to be generated


### Turrets
The turret options let you define the turrets number, name, type and characteristics.

Property name | Property type | Default value
--- | :---: | ---
tile-name | `string` | tile-set.png
types | Array of objects | see [turret type template](#turret-type-template)

##### Turret type template
Property name | Property type | Explanation
--- | :---: | ---
name | `string` | A string representing the name of the turret, this **must** be unique as it is both showed to the user in the creation menu and used to uniquely identify the turret sprite
identifier | `int` | Numeric value representing the turret unique identifier, duplicated will overwrite each other
tile-index | `int` | This value is used to clip a section of the tile and show it as the turret sprite
stats | Object | See single parameter specification
stats.cost | `int` | Numeric value representing the initial cost of the turret.<br>Note that in hard and hacked games this value is 1.5 times the defined value
stats.upgrade-cost | `int` | Numeric value representing the initial upgrade cost of the turret.<br>Note that in hard and hacked games this value is 1.5 times the defined value
stats.power | `int` | Numeric value representing the damage that each shot bullet will generate to an hit enemy
stats.fire-rate | `int` | Numeric value representing the number of bullet shot per second.<br>Note that values too high can cause graphical issue.
stats.radius | `int` | Numeric value representing the turret radius consider as a minimum a value of 60 as lesser values will never trigger the shooting loop

 
### Achievements
The achievements options let you define the achievements types, level names and goals.

Property name | Property type | Explanation
--- | :---: | ---
type | `string` | `kills / survived` This string represent the type of the achievement, in case it is set to `kills` the achievement will be considered reached when a certain number of enemies is killed otherwise the number of survived waves will trigger the event
names | Array of string | This values represent all the grade that the achievement can have once the last one is reached the achievement loops continue running but the grade will not increase anymore
first-goal | `int` | Numeric value which represent the first step of the achievements, this is the base for the following level computation
upgrade-factor | `double` | Numeric value representing the multiplication factor applies to the goal once an achievement is reached


## Maps structure
At the beginning of each map there is a comment which refer to the default version of the map.<br>
The comment is followed by a comma separated list of number which refers to the numbers of the configuration.
As you decide to change the number of turrets and assets please do not change the order of the first elements (0-4) as these
are hard-coded position used to the map rendering.

The default maps are divided into lines and columns, specifically in 32 columns (`32 * 40 = 1280` which is the default screen size) and
20 rows (`20 * 40 = 800`, the default screen height) if you decide to change the size of the window you should change the maps to reflect the
new window dimension.

Note that `easy.map` is constructed to handle only one path while `hard.map` can handle an arbitrary number of paths but to let the enemies
randomly choose a path to follow you **must specify variations**.<br>
Variation basically are map without any widget except for the **one** path and the terrain. Once an enemy is generated it randomly chose one
of the variation and follow that path.
Please note that in order to let the parser correctly parse the hard map the string `--VARIATION--` should always be present and even if the
map does not require any variation of the path a variation (representing the only path available) must always be provided.

Remember that in order to let the user place the turrets onto the map the `turret placement overlay` tile must be placed

In the following lines a small example of the `hard.map` file is given:

map dimension is `5x5` which will become after rendering a `200x200` map.
Note that in the example below turrets are not positionable on the map.
```
#####################################################
# Maps code:                                        #
#      - 0 -> Path                                  #
#      - 1 -> Terrain                               #
#      - 2 -> Tree                                  #
#      - 3 -> Rock                                  #
#      - 4 -> Turret placement overlay              #
#      - ...                                        #
#####################################################

1, 1, 1, 1, 1,
0, 0, 1, 1, 1,
1, 0, 1, 1, 1,
1, 0, 0, 0, 0,
1, 1, 1, 1, 1,

--VARIATION--

1, 1, 1, 1, 1,
0, 0, 1, 1, 1,
1, 0, 1, 1, 1,
1, 0, 0, 0, 0,
1, 1, 1, 1, 1,
```

To let the user position the turrets around the path the example above should be rewritten to:
```
... comment ...

4, 4, 4, 1, 1,
0, 0, 4, 1, 1,
4, 0, 4, 4, 4,
4, 0, 0, 0, 0,
4, 4, 4, 4, 4,

--VARIATION--

... all the desired variations ...
```

Finally a last example with multiple paths and only two places where to position turrets:
```
... comment ...

1, 1, 1, 1, 1,
0, 0, 1, 0, 0,
1, 0, 4, 0, 1,
1, 0, 0, 0, 0,
0, 0, 4, 1, 1,

--VARIATION--

1, 1, 1, 1, 1,
0, 0, 1, 1, 1,
1, 0, 1, 1, 1,
1, 0, 0, 0, 0,
1, 1, 1, 1, 1,

1, 1, 1, 1, 1,
1, 1, 1, 0, 0,
1, 1, 1, 0, 1,
1, 0, 0, 0, 1,
0, 0, 1, 1, 1,

... other variations ...
```