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
      Ok({r: num asr 16, g: num asr 8 land 255, b: num land 255})
    } else {
      Err("Can't parse Hex value")
    }
  };
  let hueToRgb = (p, q, t) => {
    let t = ref(t);
    let result = ref(p);
    if (t^ < 0.) {
      t := t^ +. 1.
    };
    if (t^ > 1.) {
      t := t^ -. 1.
    };
    if (t^ < 1. /. 6.) {
      result := p +. (q -. p) *. 6. *. t^
    };
    if (t^ < 1. /. 2.) {
      result := q
    };
    if (t^ < 2. /. 3.) {
      result := p +. (q -. p) *. (2. /. 3. -. t^) *. 6.
    };
    result^
  };
  let makeResult = (r, g, b) => {
    r: int_of_float(r *. 255.),
    g: int_of_float(g *. 255.),
    b: int_of_float(b *. 255.)
  };
  let fromHsl = ((h, s, l): hsl) : t =>
    if (s == 0.) {
      makeResult(l, l, l)
    } else {
      let q = l < 0.5 ? l *. (1. +. s) : l +. s -. l *. s;
      let p = 2. *. l -. q;
      let r = hueToRgb(p, q, h +. 1. /. 3.);
      let g = hueToRgb(p, q, h);
      let b = hueToRgb(p, q, h -. 1. /. 3.);
      makeResult(r, g, b)
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
    (h, s, l)
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