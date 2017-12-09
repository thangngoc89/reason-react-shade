module Color: {
  type t;
  let toRgb: t => (int, int, int);
  let toHsl: t => (float, float, float);
  let fromHex: string => option(t);
  let toHex: t => string;
} = {
  type t = {
    r: int,
    g: int,
    b: int
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
  let fromHex = (hex) => {
    let length = String.length(hex);
    if (length === 6) {
      let num = int_of_string("0x" ++ hex);
      Some({r: num asr 16, g: num asr 8 land 255, b: num land 255})
    } else {
      None
    }
  };
  /* Optimized JS code should be
     function (r,g,b) => ((b | g << 8 | r << 16) | 0x1000000).toString(16).substring(1);
     */
  let hex_of_int = (a) => Printf.sprintf("%02x", a);
  let toHex = ({r, g, b}) =>
    b lor g lsl 8 lor r lsl 16 lor 0x1000000 |> hex_of_int |> Js.String.substr(~from=1);
};
/* Js.log(toHex(0, 204, 255)); */