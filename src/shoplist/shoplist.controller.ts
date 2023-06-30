import {
  Body,
  Controller,
  Get,
  Post,
  Res,
  Session,
  UseGuards,
} from '@nestjs/common';
import { AuthenticatedGuard } from 'src/auth/authenticated.guard';
import { UserService } from 'src/user/user.service';
import { ShoplistService } from './shoplist.service';

@Controller('dashboard')
export class ShoplistController {
  constructor(
    private readonly shoplistService: ShoplistService,
    private readonly userService: UserService,
  ) {}

  @UseGuards(AuthenticatedGuard)
  @Post('api/bestill')
  async logg(@Body() shoplist, @Session() bruker, @Res() res) {
    const dropSted = shoplist[0]; // Dropsted er ALLTID det første element i arrayet

    // Komponenter er ALLTID resten av arrayet, og må extractes fra det ytre attayet
    // Ser egentlig sånn ut: shoplist = [dropSted, [komponenter]]
    const [komponenter] = shoplist.slice(1);

    const user = await this.userService.findById(bruker.passport.user);

    console.log(
      'Bestilt av',
      user.username,
      'dropSted:',
      dropSted,
      'varer:',
      komponenter,
    );

    res.send({ user, dropSted, komponenter }); // Respond med bruker, dropSted og komponenter

    return await this.shoplistService.bestillKomponenter(
      user.username,
      dropSted,
      komponenter,
    );
  }
  @Get('api/bestilling')
  async getBestilling() {
    const bestilling = this.shoplistService.getBestilling();
    return bestilling;
  }
}
