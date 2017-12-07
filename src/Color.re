type hslModel = {. "h": float, "s": float, "l": float};

/* type gradientResult = {. "from": string, "to_": string, "light": Js.boolean};

   [@bs.module "./ColorProcess.js"]
   external gradient :
     (~base: string, ~hueShift: int, ~saturate: int, ~lighten: int) => gradientResult =
     "gradient"; */
type gradientResult = {
  start: string,
  finish: string,
  light: bool
};

[@bs.module "./ColorProcess.js"]
external jsGradient :
  (~base: string, ~hueShift: int, ~saturate: int, ~lighten: int) =>
  {. "from": string, "to_": string, "light": Js.boolean} =
  "gradient";

let gradient = (~base: string, ~hueShift: int, ~saturate: int, ~lighten: int) => {
  let result = jsGradient(~base, ~hueShift, ~saturate, ~lighten);
  {start: result##from, finish: result##to_, light: Js.to_bool(result##light)}
};

[@bs.module "./ColorProcess.js"] external hsl : string => hslModel = "hsl";

[@bs.module "./ColorProcess.js"] external hex_of_hsl : (float, float, float) => string =
  "hex_of_hsl";