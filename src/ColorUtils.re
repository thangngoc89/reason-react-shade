type rgb = {
  r: int,
  g: int,
  b: int
};

type rgba = {
  r: int,
  g: int,
  b: int,
  a: float
};

type hsl = {
  h: float,
  s: float,
  l: float
};

type hsla = {
  h: float,
  s: float,
  l: float,
  a: float
};

let rgbToHsl = (source: rgb) => {
  let r = float_of_int(source.r) /. 255.;
  let g = float_of_int(source.g) /. 255.;
  let b = float_of_int(source.b) /. 255.;
  let cMax = max(r, max(b, g));
  let cMin = min(r, min(b, g));
  let c = cMax -. cMin;
  let h =
    (
      if (cMax == r) {
        (g -. b) /. c
      } else if (cMax == g) {
        2. +. (b -. r) /. c
      } else {
        4. +. (r -. g) /. c
      }
    )
    *. 60.;
  let l = (cMax +. cMin) /. 2.;
  let s =
    if (l == 0.) {
      0.
    } else {
      c /. (1. -. abs_float(2. *. l -. 1.))
    };
  {h, s, l}
};