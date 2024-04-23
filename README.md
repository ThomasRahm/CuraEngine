# The old read-me explaining the tree support settings can be found [here](https://github.com/ThomasRahm/CuraEngine/tree/tree_support_2_error_detection)

# Tree Support Cradle Generation

One issue of tree supports is that pointy overhangs are more prone to failing. This tries to solve this by surrounding the model with lines orthogonal to the model outline. These lines can then be folded over to remove them from the model.

![Example Cradle](https://gist.githubusercontent.com/ThomasRahm/4085f269c710a517ee1d9fcfe11976f8/raw/Example.PNG)


# Download and Installation (Link will be added soon)

Copy the CuraEngine.exe and the folder in the zip to your Cura installation of the corresponding version. To remove reinstall said Cura version. Note that the new settings will not be visible by default.

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
  <summary>Cradle Tip Size</summary>

  Percentage of size of the tips supporting the pointy overhang. 0% means the tip with have the size of regular tips. 100% means they will have a diameter of branch diameter.  
   

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

## Currently known limitations:
- If custom angles are set for the infill the result may not be what the end-user expects.
- Enforce Initial Layer Diameter may cause an effectively higher Branch Density. When tips are multiple mm large, placing one tip ever few cm seems counter productive.
- Cradle XY distance can be larger than intended if the line hits the model at a small angle, especially if the model surface is uneven. This is rare though.
- As cradle lines that would collide with branches are removed, but cradle lines are elongated to prevent overhang at the end of the line, some lines may be larger than `Cradle Length`

## Things that should be done
- Reducing the amount of settings (I would like some input in that regard) 
- Evaluating what the default settings should be.
