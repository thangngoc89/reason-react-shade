type gradientResult = {. "from": string, "to_": string, "light": bool};

type hslModel = {. "h": float, "s": float, "l": float};

/* base, hueShift, saturate, lighten */
[@bs.module "./ColorProcess.js"]
external gradient :
  (~base: string, ~hueShift: int, ~saturate: int, ~lighten: int) => gradientResult =
  "gradient";

[@bs.module "./ColorProcess.js"] external hsl : string => hslModel = "hsl";

[@bs.module "./ColorProcess.js"] external hex_of_hsl : (float, float, float) => string =
  "hex_of_hsl";