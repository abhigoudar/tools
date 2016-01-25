/** Tool for arma::mat to opencv::mat conversion
 * src is the source arma matrix
 */
 
void to_cvmat(mat map)
{
  cv::Mat_<double> map_image(map.n_rows,map.n_cols,map.memptr());
  map_image = map_image.t();   // to account for the row/col discrepency between opencv and armadillo
  cv::namedWindow("Map", cv::WINDOW_AUTOSIZE );
  cv::imshow("Map", map_image);
  cv::waitKey(0);
}
