open Utils;

type rgb = (int, int, int);

type hsl = (float, float, float);

module Converter: {
  type t;
  let fromHex: string => result(t, string);
  let fromRgb: rgb => t;
  let fromHsl: hsl => t;
  let toRgb: t => rgb;
  let toHsl: t => hsl;
  let toHex: t => string;
  let dark: t => bool;
  let light: t => bool;
} = {
  type t = {
    r: int,
    g: int,
    b: int
  };
  let fromRgb = ((r, g, b)) => {r, g, b};
  let fromHex = (hex) => {
    let length = String.length(hex);
    if (length === 6) {
      let num = int_of_string("0x" ++ hex);
      Ok({r: num asr 16, g: num asr 8 land 0xFF, b: num land 0xFF})
    } else {
      Err("Can't parse Hex value")
    }
  };
  let fromHsl = ((h, s, l): hsl) : t => {
    let h = h /. 360.;
    let s = s /. 100.;
    let l = l /. 100.;
    let t1 = ref(0.);
    let t2 = ref(0.);
    let t3 = ref(0.);
    let value = ref(0.);
    let r = ref(0);
    let g = ref(0);
    let b = ref(0);
    if (s == 0.) {
      let result = l *. 255.;
      {r: int_of_float(result), g: int_of_float(result), b: int_of_float(result)}
    } else {
      if (l < 0.5) {
        t2 := l *. (1. +. s)
      } else {
        t2 := l +. s -. l *. s
      };
      let oneThird = 1. /. 3.;
      t1 := 2. *. l -. t2^;
      for (i in 0 to 2) {
        t3 := h +. oneThird *. (-. (float_of_int(i) -. 1.));
        t3 :=
          (
            if (t3^ < 0.) {
              t3^ +. 1.
            } else if (t3^ > 1.) {
              t3^ -. 1.
            } else {
              t3^
            }
          );
        if (6. *. t3^ < 1.) {
          value := t1^ +. (t2^ -. t1^) *. 6. *. t3^
        } else if (2. *. t3^ < 1.) {
          value := t2^
        } else if (3. *. t3^ < 2.) {
          value := t1^ +. (t2^ -. t1^) *. (2. /. 3. -. t3^) *. 6.
        } else {
          value := t1^
        };
        if (i == 0) {
          r := int_of_float(value^) * 255
        } else if (i == 1) {
          g := int_of_float(value^) * 255
        } else if (i == 2) {
          b := int_of_float(value^) * 255
        }
      };
      {r: r^, g: g^, b: b^}
    }
  };
  let toRgb = ({r, g, b}) => (r, g, b);
  let toHsl = ({r, g, b}) => {
    let r = float_of_int(r) /. 255.;
    let g = float_of_int(g) /. 255.;
    let b = float_of_int(b) /. 255.;
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
    (h, s *. 100., l *. 100.)
  };
  /* Optimized JS code should be
     function (r,g,b) => ((b | g << 8 | r << 16) | 0x1000000).toString(16).substring(1);
     */
  let hex_of_int = (a) => Printf.sprintf("%02x", a);
  let toHex = ({r, g, b}) =>
    b lor g lsl 8 lor r lsl 16 lor 0x1000000 |> hex_of_int |> Js.String.substr(~from=1);
  let dark = ({r, g, b}) : bool => {
    /* YIQ equation from http://24ways.org/2010/calculating-color-contrast */
    let yiq = (r * 299 + g * 587 + b * 114) / 1000;
    yiq < 129
  };
  let light = (color) : bool => ! dark(color);
};

module Manipulation = {
  let rotate = (degrees, color: hsl) : hsl => {
    let (h, s, l) = color;
    let h = mod_float(h +. degrees, 360.);
    let h = h < 0. ? 360. +. h : h;
    (h, s, l)
  };
  let saturate = (ratio, color: hsl) : hsl => {
    let (h, s, l) = color;
    let s = s +. s *. ratio;
    (h, s, l)
  };
  let desaturate = (ratio, color: hsl) : hsl => {
    let (h, s, l) = color;
    let s = s -. s *. ratio;
    (h, s, l)
  };
  let lighten = (ratio, color: hsl) : hsl => {
    let (h, s, l) = color;
    let l = l +. s *. ratio;
    (h, s, l)
  };
  let darken = (ratio, color: hsl) : hsl => {
    let (h, s, l) = color;
    let l = l -. s *. ratio;
    (h, s, l)
  };
};