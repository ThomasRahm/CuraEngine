# The old read-me explaining the tree support settings can be found [here](https://github.com/ThomasRahm/CuraEngine/tree/tree_support_2_error_detection)

# Tree Support Cradle Generation

One issue of tree supports is that pointy overhangs are more prone to failing. This tries to solve this by surrounding the model with lines orthogonal to the model outline. These lines can then be folded over to remove them from the model.

![Example Cradle](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Example.PNG)


# [Download](https://github.com/ThomasRahm/CuraEngine/releases/tag/5.10.TS2_Cradle.R3) and Installation

Install permanently:
Paste the content of this zip into your Cura 5.10 installation directory to install it (replacing CuraEngine.exe).
To remove it remove Cura 5.10, delete the remaining folders in your installation directory and then install Cura 5.10 again.

Install temporarily:
If you want to use this and the regular Cura 5.10 at the same time, __copy__ your Cura 5.10 installation into another folder and follow the installation as if this new folder were your installation directory(Paste the content of this zip into it, replacing CuraEngine.exe).  
To run the modified Cura start the **UltiMaker-Cura.exe** in said directory.
To remove just delete the copy of your Cura installation that you copied the files into.

__Note that the new settings will not be visible by default.__

# Defect intensity of cradle connection

Every support that connects with the model causes some defects. For cradle support I consider the intensity to be low if the cradle xy distances are configured correctly and very low if fine-tuned.

<details>
  <summary>Cradle Defect Intensity (20x magnification)</summary>
  
  ![Cradle Defects 1](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Cradle%2520Defects%25202.jpg)

</details>

<details>
  <summary>Cradle Defect Intensity Fine-tuned (20x magnification)</summary>

  ![Cradle Defects 2](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Cradle%2520Defects%25201.jpg)
  
</details>

# Settings:

<details>
  <summary>Enforce Initial Layer Diameter</summary>

   Enlarge tips so that the branch could reach Initial layer Diameter. This should improve the tree supports ability to support areas very close to the buildplate. Enabling support skin or using support roof is strongly recommended.

   Disabled:
   ![Enforce Initial Layer Diameter Off](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Enforce%2520Initial%2520Layer%2520Diameter%2520Off.png)
   
   Enabled:
   ![Enforce Initial Layer Diameter On](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Enforce%2520Initial%2520Layer%2520Diameter%2520On.png)

  
</details>

<details>
  <summary>Cradle Height</summary>

   The height of the cradle to support pointy overhangs. The cradle will stop generating if the pointy part of the model connects with another part of the model that either rests on the buildplate or already has its own cradle. Set to 0 to disable.  


   Small Cradle Height:
   ![Small Cradle Height](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Small%2520Cradle%2520Height.png)
   
   Large Cradle Height:
   ![Large Cradle Height](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Large%2520Cradle%2520Height.png)

  
</details>

<details>
  <summary>Minimum Cradle Height</summary>

   If a cradle smaller than this would generate, it just doesn't.
  

</details>

<details>
  <summary>Cradle Lines</summary>

  Amount of lines that should be generated around the model.  
   

   Low Amount Of Cradle Lines:
   ![Low Amount Of Cradle Lines](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Small%2520Cradle%2520Line%2520Count.png)
   
   Large Amount Of Cradle Lines:
   ![Large Amount Of Cradle Lines](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Large%2520Cradle%2520Line%2520Count.png)

  
</details>

<details>
  <summary>Cradle Length</summary>

  Length of the lines that generate around the model.  
   

   Small Cradle Length:
   ![Small Cradle Length](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Short%2520Cradle%2520Length.png)
   
   Large Cradle Length:
   ![Large Cradle Length](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Long%2520Cradle%2520Length.png)

  
</details>

<details>
  <summary>Cradle Line Width</summary>

  Width of the lines that generate around the model. I would just hard-code this to line width.  
   

   Small Cradle Line Width:
   ![Small Cradle Line Width](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Small%2520Cradle%2520Line%2520Width.png)
   
   Large Cradle Line Width:
   ![Large Cradle Line Width](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Large%2520Cradle%2520Line%2520Width.png)

  
</details>

<details>
  <summary>Cradle Threshold</summary>

  Maximum area a pointy overhang may have for the cradle to generate.  
  
</details>

<details>
  <summary>Cradle Base Support Area Diameter</summary>

  Size of the tips below an pointy overhang overhang. Also the size of tips below lines if `Large Cradle Line Tips` is active and the roof base if `Cradle Roof Type` is `Large Cradle and Base`  
   

   Small Cradle Tip Size:
   ![Small Cradle Line Width](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Small%2520Cradle%2520Tips.png)
   
   Large Cradle Tip Size:
   ![Large Cradle Line Width](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Large%2520Cradle%2520Tips.png)

  
</details>

<details>
  <summary>Cradle XY Distance</summary>

  Distance of the cradle lines from the model, dependent on the height of cradle lines below it (Cradle XY distance)  
   

   Visualisation: 
   ![Visualisation](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Cradle%2520XY%2520Distance.png)

  
</details>

<details>
  <summary>Cradle Z Distance</summary>

  Distance between cradle lines and the support that supports them. Makes cradle lines easier to fold over.  

  
</details>

<details>
  <summary>Large Cradle Line Tips</summary>

  Generate large tips below the cradle lines.
   

   Tree Support Large Cradle Line Tips Off:
   ![Tree Support Large Cradle Line Tips Off](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Large%2520Cradle%2520Line%2520Tips%2520off.png)
   
   Tree Support Large Cradle Line Tips On: 
   ![Tree Support Large Cradle Line Tips On](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Large%2520Cradle%2520Line%2520Tips%2520on.png)

  
</details>


<details>
  <summary>Cradle Line Direction</summary>
  Whether the cradle lines targets the center of mass of the object or targets the object outline.

   Center Of Mass:
   ![Center Of Mass](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Cradle%2520Line%2520Direction%2520Center.png)
   
   Closest Outline: 
   ![Closest Outline](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Cradle%2520Line%2520Direction%2520Closest.png)
  
</details>


<details>
  <summary>Cradle Roof Type</summary>

  How the cradle behaves if roof is enabled.  
   

   Regular Support
   ![Regular Support](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Cradle%2520Roof%2520Regular.png)
   
   Cradle:
   ![Cradle](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Cradle%2520Roof%2520Cradle.png)

  Cradle and Base:
   ![Cradle and Base](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Cradle%2520Roof%2520Cradle%2520and%2520Base.png)
   
   Large Cradle and Base:
   ![Large Cradle and Base](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Large%2520Cradle%2520and%2520Base.png)

  
</details>

<details>
  <summary>Support Skin Height</summary>
  
  Height of Support Skin generated to support cradle/interface/model parts that would fall inside of a support area. What i call Support Skin is just a support area with high density zig-zag infill.

   
   Small Support Skin Height:
   ![Small Support Skin Height](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Low%2520Skin%2520Height.png)
   
   Large Support Skin Height: 
   ![Large Support Skin Height](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Large%2520Skin%2520Height.png)

  
</details>

<details>
  <summary>Support Skin Line Distance</summary>
  Distance between the lines for said high density support infill.
   
   Small Support Skin Line Distance:
   ![Small Support Skin Line Distance](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Small%2520Skin%2520Line%2520Distance.png)
   
   Large Support Skin Line Distance: 
   ![Large Support Skin Line Distance](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Large%2520Skin%2520Line%2520Distance.png)
  
</details>

<details>
  <summary>Support Skin for Tips Threshold</summary>
  
  Generate support skin for any tips that have at least this diameter.
   
  
</details>

<details>
  <summary>Automatic Side Cradle Generation</summary>
  
  Thin objects can bend while printing. This enables automatic placements of cradles to try to stabilize such parts.
   
  
</details>

<details>
  <summary>Side Cradle Stable Part Diameter</summary>
  
  Parts with a footprint of at least this size are considered to not be bending.
   
  
</details>

<details>
  <summary>Side Cradle Displacement Constant</summary>
  This describes the tendency of parts bending while printing. Higher values represent higher bendability and lead to more side cradles.
  
</details>

<details>
  <summary>Side Cradle Displacement Threshold</summary>
  
  How far may a part bend before a cradle is placed. This assumes that the Side Cradle Displacement Constant is correctly representing the bendability of the material and applied forces to said material. Should be between 0.2mm and 0.8mm. Lower values result in more placed side cradles.
   
  
</details>

<details>
  <summary>Side Cradle Displacement Horizontal Factor</summary>
  
  If a part is not just straight up, but placed at an angle (relative to the buildplate) the bending of the part leads to it being pushed down. As soon as the nozzle leaves the part, it will spring up a bit, leading to nozzle collisions. As such any displacement coming from a part with a horizontal distance between bending point and currently printed area should be overestimated regarding bending to prevent any print-failures. This factor describes the overestimation of the bending.  
   
  
</details>


# Support Blocker Setting Change

An option to manually place a cradle was added. Note that this just tags the model part to be supported with a cradle, so the only thing that matters is that the support modifier overlaps with the part of the model that should be supported with a cradle. The most-down outline that overlaps with the modifier will be the first layer that will be supported with a cradle.

Further, a more nuanced setting for support blocker was added. It now is possible to choose between no model in the overlapping area will be supported vs no support will pass through the area of the support modifier. 

<details>
  <summary>Support Blocker Setting Change Menu</summary>
  
   ![Support Blocker Setting Change Menu](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Support%2520Blocker%2520Settings.png)
</details>

The font-end code changes can be found [here](https://github.com/ThomasRahm/Cura/tree/manual_cradle_placement)

# Code

The code is in a separate branch found [here](https://github.com/ThomasRahm/CuraEngine/tree/tree_support_2).
The readme is in a separate branch to exclude it from the corresponding [pull request](https://github.com/Ultimaker/CuraEngine/pull/1880).


## Currently known limitations:
- If custom angles are set for the support infill the resulting skin may not be what the end-user expects.
- Enforce Initial Layer Diameter may cause an effectively higher Branch Density. When tips are multiple mm large, placing one tip ever few cm seems counter productive.
- Cradle XY distance can be larger than intended if the line hits the model at a small angle, especially if the model surface is uneven. This is rare though.
- As cradle lines that would collide with branches are removed, but cradle lines are elongated to prevent overhang at the end of the line, some lines may be larger than `Cradle Length`
- Large thin parts that start in mid-air (e.g. horizontal swords) may not get a cradle placed to support it (based on `Cradle Threshold`). This is not optimal yet. Further increasing the amount of either center-points or cradle lines would be beneficial for such objects.
