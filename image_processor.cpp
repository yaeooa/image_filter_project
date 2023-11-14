#include "picture.hpp"
#include "parser.hpp"

int main(int argc, char* argv[]) {
    Parser parser(argc, argv);
    Picture picture(parser.in);
    for (auto& elem: parser.filters) {
        switch (elem.second) {
            case Parser::NEGATIVE: {
                NegativeFilter filter = std::get<NegativeFilter>(elem.first);
                picture = filter(picture);
                break;
            }
            case Parser::GRAYSCALE: {
                GrayscaleFilter filter = std::get<GrayscaleFilter>(elem.first);
                picture = filter(picture);
                break;
            }
            case Parser::SHARP: {
                SharpeningFilter filter = std::get<SharpeningFilter>(elem.first);
                picture = filter(picture);
                break;
            }
            case Parser::EDGE: {
                EdgeFilter filter = std::get<EdgeFilter>(elem.first);
                picture = filter(picture);
                break;
            }
            case Parser::CROP: {
                CropFilter filter = std::get<CropFilter>(elem.first);
                picture = filter(picture);
                break;
            }
            case Parser::PIXELLATE: {
                PixellateFilter filter = std::get<PixellateFilter>(elem.first);
                picture = filter(picture);
                break;
            }
            case Parser::BLUR: {
                BlurFilter filter = std::get<BlurFilter>(elem.first);
                picture = filter(picture);
                break;
            }
        }
    }
    picture.WriteFile(parser.out);
}
