open Aim;
open Elements;

let createElement = (~children, ()) => {
  statelessComponent(<> <div> {text("path not found.")} </div> </>, _ => ());
};
