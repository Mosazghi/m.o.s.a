import { Body, Controller, Post, Session, UseGuards } from '@nestjs/common';
import { AuthenticatedGuard } from 'src/auth/authenticated.guard';
import { UserService } from 'src/user/user.service';
import { CreateShoplistDto } from './dto/create-shoplist.dto';
import { ShoplistService } from './shoplist.service';

@Controller('dashboard')
export class ShoplistController {
  constructor(
    private readonly shoplistService: ShoplistService,
    private readonly userService: UserService,
  ) {}

  @UseGuards(AuthenticatedGuard)
  @Post()
  async logg(@Body() shoplist, @Session() bruker) {
    //bruker.passport.user
    const user = await this.userService.findById(bruker.passport.user);
    console.log('Bestilt av', user.username, 'varer:', shoplist);
  }
}
