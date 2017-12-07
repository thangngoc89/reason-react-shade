type gradientResult = {. "from": string, "to_": string, "light": bool};

/* base, hueShift, saturate, lighten */
[@bs.module "./ColorProcess.js"]
external gradient :
  (~base: string, ~hueShift: int, ~saturate: int, ~lighten: int) => gradientResult =
  "gradient";