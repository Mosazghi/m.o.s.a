import { Injectable } from '@nestjs/common';
import { InjectModel } from '@nestjs/mongoose';
import { Model } from 'mongoose';
import { CreateShoplistDto } from './dto/create-shoplist.dto';
import { Shoplist } from './schema/shoplist.schema';
import { ShoplistType } from './type/shoplist.type';

@Injectable()
export class ShoplistService {
  constructor(
    @InjectModel(Shoplist.name) private readonly shoplistModel: Model<Shoplist>,
  ) {}
  async bestillKomponenter(bruker: string, komponenter: ShoplistType[]) {
    const test = { bruker, komponenter };
    const bestill = await new this.shoplistModel(test);
    console.log('BESTILL:', bestill);
    return bestill.save();
  }
}
