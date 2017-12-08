type hslModel = {. "h": float, "s": float, "l": float};

type gradientResult = {
  start: string,
  finish: string,
  light: bool
};

[@bs.module "./ColorProcess.js"]
external jsGradient :
  (~base: string, ~hueShift: float, ~saturate: float, ~lighten: float) =>
  {. "from": string, "to_": string, "light": Js.boolean} =
  "gradient";

let gradient = (~base: string, ~hueShift: float, ~saturate: float, ~lighten: float) => {
  let result = jsGradient(~base, ~hueShift, ~saturate, ~lighten);
  {start: result##from, finish: result##to_, light: Js.to_bool(result##light)}
};

[@bs.module "./ColorProcess.js"] external hsl : string => hslModel = "hsl";

[@bs.module "./ColorProcess.js"] external hex_of_hsl : (float, float, float) => string =
  "hex_of_hsl";