/* 
 * NOTE -- this is an overly simplistic binding for css-in-js 
 * however, for the time being it will allow writing in _actual css_, not a DSL
 * and still authoring in modern-JS "everything in a single file type of fashion"
 */
[@bs.module "emotion"] external css : string => string = "css";